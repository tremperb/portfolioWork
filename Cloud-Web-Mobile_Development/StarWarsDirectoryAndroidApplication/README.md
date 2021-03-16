## Star Wars Directory Mobile Android Application(Prototype)

Created by: Brayden Tremper, Justin Vaughn, Juichi Lee, and YiDong Lin.


#A high-level description of what your app will do.

Our app will allow the user to search for any planet, spaceship, vehicle, person, films, and species from the Star Wars franchise. For instance, the user can choose a category in the main screen and a comprehensive list of things pertaining that category will show up. Then, the user can further narrow their search by typing in the name of their search. Furthermore, the user can also click on one of the results in the list and get a detailed view on that result. While the user is using the application, the main Star Wars theme will be played in the background and different sound cues will be whenever the user clicks a button. In the main activity’s options, the user can turn on or off the background music and switch the music themes between Jedi and Sith. In the detailed view of an item, the user can also perform a google images search of the item.  

#A link to the specific 3rd-party API your app will use, an explanation of the API methods your app will call, and a description of how the data from those methods will be used in your app or what data will be sent from your app to the API.

https://swapi.dev/ We will be using a combination of the GET functions for people, planets, films, species, people, starships, and vehicles to allow a user better understanding of the Star Wars universe. We will be sending base queries for each category to build an initial view and will get back a list of options. Each category will have a search that will send a query phrase and get back a JSON object of that query.

#A description of how the UI for your app will be organized, including a list of your app’s activities, a description of how the user will navigate between those activities, a description of any major non-navigation interactions available to the user, and a description of any notifications the app will display.

The app will have a main activity that has the app name at the top and 6 buttons, each representing a category the user can choose to search from. Clicking on a button will take the user to the activity for that category. Upon entering a category activity, the activity will have prepared a list of items for the user to look through. The user can enter a name in a search bar at the top to narrow their search. Furthermore, the user can click on an item in the list and receive a detailed view of the item. The detailed views and category activities all have back buttons for the user to navigate back to a category activity or the main activity. The main activity will have a settings option that allows the user to turn on or off the Star Wars background music, change its volume, and to switch between a Sith theme or a Jedi theme. Each detailed view will have an option for the user to automatically search for images of the item using google images. 

#A description of the additional feature not covered in class that your app will implement.

We will be playing the Star Wars theme as background music for the app. The song will start when the app is opened but will not include playing if the screen is turned off. The settings will have the ability to turn the sound down/off for the song but not stop or start it over.


