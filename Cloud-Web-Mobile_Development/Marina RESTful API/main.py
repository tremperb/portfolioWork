# Name: Brayden Tremper
# Email: tremperb@oregonstate.edu
# Date: 10/25/2020
# Description: HW4, Rest API for marina, using python

import json
from requests_oauthlib import OAuth2Session
import string
import flask
import constants

from google.cloud import datastore
from flask import Flask, render_template, request
from google.oauth2 import id_token
from google.auth import crypt
from google.auth import jwt
from google.auth.transport import requests

import os
os.environ['OAUTHLIB_INSECURE_TRANSPORT'] = '1'

app = flask.Flask(__name__)
client = datastore.Client()

import uuid
app.secret_key = str(uuid.uuid4())
app.debug = True

with open('client_secret.json') as f:
    client_secret_data = json.load(f)


# everything besides scope is in the secret file, so.. might as well load it
client_id = client_secret_data['web']['client_id']
client_secret = client_secret_data['web']['client_secret']
scope = 'https://www.googleapis.com/auth/userinfo.profile'
redirect_uris = list(client_secret_data['web']['redirect_uris'])


oauth = OAuth2Session(client_id, redirect_uri=redirect_uris[0],
                          scope=scope)


def verify_jwt(my_jwt):
    req = requests.Request()

    # Go ahead and try to see if it works
    try:
        id_info = id_token.verify_oauth2_token(
        my_jwt, req, client_id)
    except:
        return False # uh oh just return false so we can take our next course of action
    else:
        # It worked
        return id_info



@app.route('/')
def index():
    authorization_url, state = oauth.authorization_url(
        'https://accounts.google.com/o/oauth2/auth',
        # access_type and prompt are Google specific extra
        # parameters.
        access_type="offline", prompt="select_account")

    html = ''
    html = "<link rel='stylesheet' type='text/css' href='static/infoPage.css?v=0'>"
    html += "<body><section class='myHead' id='myHead'>"
    html += "<h1><u>Welcome! Login Below</u></h1>"
    html += "<a class='button' id='button' href='%s'>Google Login</a>"  % authorization_url# link to login
    html += "<br><br><br>"
    html += "</section></body>"
    return html#'Please go <a href=%s>here</a> and authorize access.' % authorization_url


# This is where users will be redirected back to and where you can collect
# the JWT for use in future requests
@app.route('/oauth')
def oauthroute():
    token = oauth.fetch_token(
        'https://accounts.google.com/o/oauth2/token',
        authorization_response=request.url,
        client_secret=client_secret)
    req = requests.Request()

    id_info = id_token.verify_oauth2_token(
    token['id_token'], req, client_id)

    return flask.redirect(flask.url_for('user', jwt=token['id_token']))#"Your JWT is: %s" % token['id_token']


@app.route('/userInfo')
def user():
    req = requests.Request()
    if 'jwt' not in request.args: # does it have a jwt?
        return flask.redirect(flask.url_for('index'))   # if not rerturn to main page to have them log in

    try:
        id_info = id_token.verify_oauth2_token(request.args['jwt'], req, client_id)
    except:
        return flask.redirect(flask.url_for('index'))   # if not rerturn to main page to have them log in

    # is it valid still?
    if id_info['exp'] <= 0:
        return flask.redirect(flask.url_for('index'))
    else:
        new_user_info = verify_jwt(request.args['jwt'])
        alreadyAdded = False

        # Check if already registered
        query = client.query(kind=constants.users)
        results = list(query.fetch())

        for e in results:
            if 'userID' in e:
                if e["userID"] == new_user_info["sub"]:
                    alreadyAdded = True

        if alreadyAdded == False:
            new_user = datastore.entity.Entity(key=client.key(constants.users))
            new_user.update({"userID": new_user_info["sub"]})
            client.put(new_user)
        #
        #
        ourReturn = ({"Your JWT": request.args['jwt'], "Your userID": new_user_info["sub"]})
        return json.dumps(ourReturn)#("Your JWT is: %s" % request.args['jwt'], "Your userID is: %s" % new_user_info["sub"])


@app.route('/users', methods=['GET'])
def getUsers():
    query = client.query(kind=constants.users)
    results = list(query.fetch())
    output = {"AuthorizedUsers": results}
    return json.dumps(output)
# Get and Post methods
# responsible for creating a boat and getting all boats
# pagination is applied
# ------
@app.route('/boats', methods=['POST', 'GET'])
def boats_get_post():
    if request.method == 'POST':
        #
        # Create a boat
        #

        if 'application/json' not in request.content_type:
            x =  '{ "Error": "Client sent a media type that isnt supported by this endpoint(request must be JSON)"}'
            errorMessage = json.loads(x)
            return (errorMessage, 415)

        if 'application/json' not in request.accept_mimetypes:
            x =  '{ "Error": "The requested content type is not supported by this endpoint(response must be JSON)"}'
            errorMessage = json.loads(x)
            return (errorMessage, 406)

        content = request.get_json()

        # Error Checking
        if 'name' not in content or 'type' not in content or 'length' not in content or 'public' not in content:
            x =  '{ "Error": "The request object is missing at least one of the required attributes"}'
            errorMessage = json.loads(x)
            return (errorMessage, 400)
        # End Error Checking


        try:
            theJWT = request.headers.get("authorization")
            theJWT = theJWT.replace('Bearer ', '')
        except:
            x =  '{ "Error": "You are not authorized to create a boat, please login"}'
            errorMessage = json.loads(x)
            return (errorMessage, 401)

        infoStuff = verify_jwt(theJWT)

        if infoStuff == False:
            x =  '{ "Error": "Invalid JWT"}'
            errorMessage = json.loads(x)
            return (errorMessage, 401)

        #  check if extra stuff
        # only allowed name, type, and length

        # end input validation
        # Got rid of uniqueness constraint


        # Create a new boat
        new_boat = datastore.entity.Entity(key=client.key(constants.boats))
        # store those in Datastore
        new_boat.update({"name": content["name"], "type": content["type"], "length": content["length"], "loads":[], "public": content["public"], "owner": infoStuff["sub"]})
        client.put(new_boat) # good now stores

        # These are only for response, they are not in datastore
        new_boat['id'] = str(new_boat.key.id)
        new_boat['self'] = request.url + '/' + str(new_boat.key.id)

        return (new_boat, 201)
    elif request.method == 'GET':
        authorized = True
        infoStuff = None
        # does it have that authorization?
        try:
            theJWT = request.headers.get("authorization")
            theJWT = theJWT.replace('Bearer ', '')
        except:
            # There isnt a jwt authorization
            authorized = False

        if authorized == True:

            infoStuff = verify_jwt(theJWT)

            if infoStuff == False:
                authorized = False
        # Get all the boats
        query = client.query(kind=constants.boats)
        #results = list(query.fetch())
        # list our json objects
        # Now we need to implement pagination
        # limit will be how many and offset will be the starting point
        q_limit = int(request.args.get('limit', '5'))
        q_offset = int(request.args.get('offset', '0'))
        l_iterator = query.fetch(limit= q_limit, offset= q_offset)
        pages = l_iterator.pages
        results = list(next(pages))
        # Now we have that reinitialize the offset to have the limit added for next time
        if l_iterator.next_page_token:
            next_offset = q_offset + q_limit
            next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset)
        else:
            next_url = None
        # Everything is good now assign id and self stuff for response
        for e in results:
            e["id"] = e.key.id
            e["self"] = request.url_root + 'boats/' + str(e.key.id)
            # Make sure that this load isnt assigned to another boat already
            for i in e["loads"]:
                if 'id' in i:
                    i["self"] = request.url_root + 'loads/' + i['id']

        # Change based on authorization
        if authorized == True:
            # get all boats for that jwt
            myResults = []
            # if the owner isnt our decoded sub property then we dont want it
            for e in results:
                if e["owner"] == infoStuff["sub"]:
                    myResults.append(e)

            return (json.dumps(myResults), 200)
        else:
            myResults = []
            # ONLY GETTING PUBLIC BOATS THAT CAN BE FROM ANYONE
            for e in results:
                if e["public"] == True:
                    myResults.append(e)

        output = {"boats": myResults}
        # store the output
        # include the next link if it has another page
        if next_url:
            output["next"] = next_url
        # good send response
        return (json.dumps(output), 200)
    else:
        return "Method not associated with this page"

# Get and Post methods
# responsible for creating a load and getting all loads
# pagination is applied
# ------
@app.route('/loads', methods=['POST', 'GET'])
def loads_get_post():
    if request.method == 'POST':

        # Make sure we have all fields
        content = request.get_json()
        # Error Checking
        # weight, content, delivery_date
        if 'weight' not in content or 'content' not in content or 'delivery_date' not in content:
            x =  '{ "Error": "The request object is missing at least one of the required attributes"}'
            errorMessage = json.loads(x)
            return (errorMessage, 400)
        # End Error Checking

        # get our entities of type loads
        new_load = datastore.entity.Entity(key=client.key(constants.loads))
        new_load.update({"weight": content["weight"], "content": content["content"], "delivery_date": content["delivery_date"], "carrier": None})
        client.put(new_load)
        # Add the new load

        # create these for response but not stored in datastore
        new_load['id'] = str(new_load.key.id)
        new_load['self'] = request.url + '/' + str(new_load.key.id)

        return (new_load, 201)
    elif request.method == 'GET':
        # Get every load
        query = client.query(kind=constants.loads)

        # implement pagination with the loads too
        #  same approach
        q_limit = int(request.args.get('limit', '5'))
        q_offset = int(request.args.get('offset', '0'))
        l_iterator = query.fetch(limit= q_limit, offset= q_offset)
        pages = l_iterator.pages
        results = list(next(pages))
        if l_iterator.next_page_token:
            next_offset = q_offset + q_limit
            next_url = request.base_url + "?limit=" + str(q_limit) + "&offset=" + str(next_offset)
        else:
            next_url = None

        # add in no datastore items
        for e in results:
            e["id"] = e.key.id
            e["self"] = request.url_root + 'loads/' + str(e.key.id)
            if e["carrier"] is not None:
                e["carrier"]["self"] = request.url_root + 'boats/' + e["carrier"]["id"]
        output = {"loads": results}
        if next_url:
            output["next"] = next_url

        return (json.dumps(output), 200)

# PATCH GET AND DELETE METHODS
# responsible updating a boat, deleting, and getting a single boat
# ------
@app.route('/boats/<id>', methods=['PATCH', 'DELETE', 'GET'])
def boats_put_delete(id):
    if request.method == 'PATCH':



        # make sure request content is good
        content = request.get_json()

        # Start Error Checking
        if 'name' not in content or 'type' not in content or 'length' not in content or 'public' not in content:
            x =  '{ "Error": "The request object is missing at least one of the required attributes"}'
            errorMessage = json.loads(x)
            return (errorMessage, 400)
        # All contents are there

        try:
            theJWT = request.headers.get("authorization")
            theJWT = theJWT.replace('Bearer ', '')
        except:
            x =  '{ "Error": "Missing JWT"}'
            errorMessage = json.loads(x)
            return (errorMessage, 401)


        infoStuff = verify_jwt(theJWT)

        if infoStuff == False:
            x =  '{ "Error": "Invalid JWT"}'
            errorMessage = json.loads(x)
            return (errorMessage, 401)
        # Okay so now we know the jwt is good


        # make sure that boat exists
        key = client.key(constants.boats, int(id))

        # Check if valid
        query = client.query(kind=constants.boats)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(id):
                valid = True
        if valid == False:
            x =  '{ "Error": "No boat with this boat_id exists"}'
            errorMessage = json.loads(x)
            return (errorMessage, 403)
        # End check
        # End check
        # End Error Checking

        # Valid boat and jwt but... is this boat owned by them?


        # Now we know its therer so update it
        boat = client.get(key=key)

        # Is it owned by this person tho..?
        if boat["owner"] == infoStuff["sub"]:
            boat.update({"name": content["name"], "type": content["type"], "length": content["length"]})
            client.put(boat)
            # get non datastore items
            boat['id'] = str(boat.key.id)
            boat['self'] = request.url
            return (boat, 200)
        else:
            x =  '{ "Error": "This boat is owned by somebody else"}'
            errorMessage = json.loads(x)
            return (errorMessage, 403)
    elif request.method == 'DELETE':
        #
        # Delete A Boat
        #

        try:
            theJWT = request.headers.get("authorization")
            theJWT = theJWT.replace('Bearer ', '')
        except:
            x =  '{ "Error": "Missing JWT"}'
            errorMessage = json.loads(x)
            return (errorMessage, 401)


        infoStuff = verify_jwt(theJWT)

        if infoStuff == False:
            x =  '{ "Error": "Invalid JWT"}'
            errorMessage = json.loads(x)
            return (errorMessage, 401)
        # Okay so now we know the jwt is good

        # make sure that boat exists
        key = client.key(constants.boats, int(id))
        # Check if valid
        query = client.query(kind=constants.boats)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(id):
                valid = True
        if valid == False:
            x =  '{ "Error": "No boat with this boat_id exists"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)
        # End check
        # Need to check if it is a carrier
        # if so set the current boat to none
        # need to get all ships and compare against boat id
        boat = client.get(key=key)
        if boat["owner"] == infoStuff["sub"]:
            for e in boat['loads']:
                if 'id' in e:
                    load_key = client.key(constants.loads, int(e["id"]))
                    load = client.get(key=load_key)
                    load.update({"carrier": None})
                    client.put(load)
            client.delete(key)
            return ('', 204)
        else:
            x =  '{ "Error": "This boat is owned by somebody else"}'
            errorMessage = json.loads(x)
            return (errorMessage, 403)
    elif request.method == 'GET':
        # The user can get a boat
        # if they are authorized they can get it if it is theirs
        # if not authorized they can only get it if it is PUBLIC
        authorized = True
        infoStuff = None
        # does it have that authorization?
        try:
            theJWT = request.headers.get("authorization")
            theJWT = theJWT.replace('Bearer ', '')
        except:
            # There isnt a jwt authorization
            authorized = False

        if authorized == True:

            infoStuff = verify_jwt(theJWT)

            if infoStuff == False:
                authorized = False

        content = request.get_json()

        # Check if valid
        query = client.query(kind=constants.boats)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(id):
                valid = True
        if valid == False:
            x =  '{ "Error": "No boat with this boat_id exists"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)
        # End check
        # Now get the individual boat
        boat_key = client.key(constants.boats, int(id))
        #
        #
        boat = client.get(key=boat_key)
        # Change based on authorization
        if authorized == True:
            if boat["owner"] == infoStuff["sub"]:
                boat['id'] = str(boat.key.id)
                boat['self'] = request.url
                for e in boat['loads']:
                    if 'id' in e: # just make sure it has that field just in case
                        e['self'] = request.url_root + 'loads/' + e['id']
                return (boat, 200)
            else:
                if boat["public"] == False:
                    x =  '{ "Error": "This boat is owned by somebody else and is not public"}'
                    errorMessage = json.loads(x)
                    return (errorMessage, 403)

        if boat["public"] == True:
            boat['id'] = str(boat.key.id)
            boat['self'] = request.url
            for e in boat['loads']:
                if 'id' in e: # just make sure it has that field just in case
                    e['self'] = request.url_root + 'loads/' + e['id']
            return (boat, 200)
        else:
            x =  '{ "Error": "This boat is owned by somebody else and is not public"}'
            errorMessage = json.loads(x)
            return (errorMessage, 403)
    else:
        return 'Unrecognized method'


# Get and DELETE methods
# responsible for deleting a single load and getting it
# ------
@app.route('/loads/<id>', methods=['DELETE', 'GET'])
def loads_put_get_delete(id):
    if request.method == 'GET':
        # verify contents
        content = request.get_json()

        # Check if valid
        query = client.query(kind=constants.loads)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(id):
                valid = True
        if valid == False:
            x =  '{ "Error": "No load with this load_id exists"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)
        # End check

        # Good get it and add non datastore items
        load_key = client.key(constants.loads, int(id))
        load = client.get(key=load_key)
        load['id'] = str(load.key.id)
        load['self'] = request.url
        if load['carrier'] is not None:
            load['carrier']['self'] = request.url_root + 'boats/' + load['carrier']['id']


        return (load, 200)
    elif request.method == 'DELETE':
        key = client.key(constants.loads, int(id))
        # Check if valid
        query = client.query(kind=constants.loads)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(id):
                valid = True
        if valid == False:
            x =  '{ "Error": "No load with this load_id exists"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)
        # End check
        load = client.get(key=key)
        boat_id = load['carrier']['id']
        boat_key = client.key(constants.boats, int(boat_id))
        boat = client.get(key=boat_key)

        for i in boat["loads"]:
            if i['id'] == id:
                # good now we can remove this load from the boat
                boat["loads"].remove(i)

        client.put(boat)

        client.delete(key) # everything good now delete
        return ('', 204)
    else:
        return 'Unrecognized method'

# PUT and DELETE methods
# put is responsible for putting a load on a boat
# the boat can have many loads but the load can only have one boat
# delete method removes the load from the boat and boat from the load
# ------
# For authorization purposes I have decided that these boats allow anyone to
# put or remove a load from a boat. Say it is sitting at a secure shipyard
# where the owner essentially rents out the boat. They still own it and are the only ones
# that can mess with it but anyone can add a load.
#
@app.route('/boats/<boat_id>/loads/<load_id>', methods=['PUT', 'DELETE'])
def assign_loads(boat_id, load_id):
    if request.method == 'PUT':
        # Check if boat valid
        query = client.query(kind=constants.boats)
        resultsBoat = list(query.fetch())
        valid = False
        for e in resultsBoat:
            if e.key.id == int(boat_id):
                valid = True
        if valid == False:
            x =  '{ "Error": "The specified boat and/or load does not exist"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)

        # Check if load is valid
        query = client.query(kind=constants.loads)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(load_id):
                valid = True
        if valid == False:
            x =  '{ "Error": "The specified boat and/or load does not exist"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)

        # Make sure that this load isnt assigned to another boat already
        for e in resultsBoat:
            for i in e["loads"]:
                if 'id' in i:
                    if i['id'] == load_id:
                        x = '{ "Error": "The specified load is already assigned to a boat"}'
                        errorMessage = json.loads(x)
                        return (errorMessage, 403)
        # Get the load
        load_key = client.key(constants.loads, int(load_id))
        load = client.get(key=load_key)

        # Get the boat
        boat_key = client.key(constants.boats, int(boat_id))
        boat = client.get(key=boat_key)

        # Got our objects
        load.update({"carrier": {"id": boat_id, "name": boat["name"]}})
        client.put(load)

        #boat.update({"loads":})

        boat['loads'].append({"id": load_id})
        client.put(boat)
        for e in boat['loads']:
            e["self"] = request.url_root + 'loads/' + e["id"]
        # putting at end to be sure we dont add to datastore

        load['id'] = str(load.key.id)
        load['self'] = request.url_root + 'loads/' + load['id']
        boat['id'] = str(boat.key.id)
        boat['self'] = request.url_root + 'boats/' + boat['id']
        load['carrier']['self'] = boat['self']

        return ('', 204)
    elif request.method == 'DELETE':
        # Check if boat valid
        query = client.query(kind=constants.boats)
        resultsBoat = list(query.fetch())
        valid = False
        for e in resultsBoat:
            if e.key.id == int(boat_id):
                valid = True
        if valid == False:
            x =  '{ "Error": "The specified boat and/or load does not exist"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)

        # Check if load is valid
        query = client.query(kind=constants.loads)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(load_id):
                valid = True
        if valid == False:
            x =  '{ "Error": "The specified boat and/or load does not exist"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)

        # Okay they are valid ids but is this load on that boat?
        # go though boat loads to check or check if the loads carrier is that boat...
        # Ig do both?
        # Get the load
        load_key = client.key(constants.loads, int(load_id))
        load = client.get(key=load_key)

        # Get the boat
        boat_key = client.key(constants.boats, int(boat_id))
        boat = client.get(key=boat_key)

        # for this load is the ship a carrier?

        if load["carrier"] is not None:
            if str(load["carrier"]["id"]) == boat_id:
                # remove that boat as a carrier
                load.update({"carrier": None})
                client.put(load)

                # remove that load from the boat
                for i in boat["loads"]:
                    if str(i["id"]) == load_id:
                        boat["loads"].remove(i)
                        client.put(boat)
                        return ('', 204)
            else:
                x =  '{ "Error": "The specified load is not being carried by this boat2"}'
                errorMessage = json.loads(x)
                return (errorMessage, 403)
        else:
            x =  '{ "Error": "The specified load is not being carried by this boat"}'
            errorMessage = json.loads(x)
            return (errorMessage, 403)

        # do rest later


    else:
        return 'Unrecognized method'

# Get  methods
# responsible for getting and displaying all
# loads for a given boat
# ------
@app.route('/boats/<boat_id>/loads', methods=['GET'])
def list_loads(boat_id):
    if request.method == 'GET':
        # Check if valid
        query = client.query(kind=constants.boats)
        results = list(query.fetch())
        valid = False
        for e in results:
            if e.key.id == int(boat_id):
                valid = True
        if valid == False:
            x =  '{ "Error": "No boat with this boat_id exists"}'
            errorMessage = json.loads(x)
            return (errorMessage, 404)
        # End check

        # Get the boat
        boat_key = client.key(constants.boats, int(boat_id))
        boat = client.get(key=boat_key)

        for e in boat["loads"]:
            if 'id' in e:
                e['self'] = request.url_root + 'loads/' + e['id']

        return (json.dumps(boat["loads"]), 200)
    else:
        return 'Unrecognized method'


if __name__ == '__main__':
    # This is used when running locally only. When deploying to Google App
    # Engine, a webserver process such as Gunicorn will serve the app. This
    # can be configured by adding an `entrypoint` to app.yaml.
    # Flask's development server will automatically serve static files in
    # the "static" directory. See:
    # http://flask.pocoo.org/docs/1.0/quickstart/#static-files. Once deployed,
    # App Engine itself will serve those files as configured in app.yaml.
    app.run(host='127.0.0.1', port=8080, debug=True)
