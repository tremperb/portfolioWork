/* This is our graph class which rrepresents our whole graph of our mst
 * using our node and point class we can get the points to find the edges
 * and then calculate those edges and print the distance and the total distance
 */

#include "graph.h"
#include <iostream>
#include <cmath>
#define INF 2147483647 //setting infinity as the max of type int

using namespace std;

Graph::Graph() {}

//non default constructor
Graph::Graph(int V) { //based on the number of vertices
    this->V = V;
    idx = -1; //used to locate each specific node
    distance = new int *[V];    //create a distance array of size V
    node = new Node[V]; //create an array to hold our nodes
    for (int i = 0; i < V; i++) {
        distance[i] = new int[V]; //get 2d bounds
    }
}

void Graph::setNode(Node node) { //setter for our node in graph
    idx++;
    this->node[idx] = node;
}

Node Graph::getNode(int in) { //return our node at the specified index
    return node[in];
}

/*Get the distance from two points*/
int Graph::getDistance(Point *a, Point *b) {

    double distanceGET = sqrt(((a->getX() - b->getX()) * (a->getX() - b->getX())) + ((a->getY() - b->getY()) * (a->getY() - b->getY())));

    int d = round(distanceGET); //round to nearest int

    return d;
}

void Graph::setGraph() {
    for (int i = 0; i < V; i++) {
        Node a = node[i];
        for (int k = 0; k < V; k++) {
            Node b = node[k];
            distance[i][k] = getDistance(a.getP(), b.getP()); //store our distance between node a and b
        }
    }
   
}

int Graph::extractMin(vector<int> key, vector<bool> set) {
    int min = INF;
    int min_index;

    for (int v = 0; v < V; v++) { //for all our vertices
        if (set[v] == false && key[v] < min) { //only if we haven't done it and its less than our key
            min = key[v];
            min_index = v;
        }
    }
    return min_index; //return our min index
}

/*
 * Now lets print our tree
 */
void Graph::printGraph(vector<int> p) {
    int total = 0;

    cout << "Point (x,y)"
         << "              "
         << "Distance" << endl;

    for (int i = 1; i < V; i++) {
        int pidx = p[i]; //parent index for where we are currently
        int xP = node[pidx].getP()->getX(); //get the coordinates of our parent
        int yP = node[pidx].getP()->getY();
        int xC = node[i].getP()->getX(); //get the childs coordinates which is where we currently are
        int yC = node[i].getP()->getY();

        cout << "(" << xP << "," << yP << ")  -  ";
        cout << "(" << xC << "," << yC << ")";
        cout << "               " << distance[i][pidx] << endl;

        total = total + distance[i][p[i]];
    }
    cout << "----------------"
         << "Total distance: " << total << endl;
}

/*
 * Now lets analyze our tree using prims algorithm
 */
void Graph::primMST() {
    vector<int> parent(V); //initiaalize our parent vector
    vector<int> key;  //the key for our tree
    vector<bool> set;  //our set to determine whether it has been used our not being of type boolean
    for (int i = 0; i < V; i++) { //for each mmaking of size V
        key.push_back(INF); //set key to infinite
        set.push_back(false); //set false since not yet viewed
    }
    key[0] = 0; 
    parent[0] = -1; //int so substituting -1 as NULL

    for (int i = 0; i < V - 1; i++) { //for each of our vertices
        int u = extractMin(key, set); //get our min value
        set[u] = true; //we have seen it so mark as true

        for (int k = 0; k < V; k++) { 
            //now if we havent seen it and our current index is less than our key
            if (distance[u][k] && set[k] == false && distance[u][k] < key[k]) {
                parent[k] = u; //set parent to hold the min
                key[k] = distance[u][k];    //update key
            }
        }
    }
    printGraph(parent); //now print our graph
}