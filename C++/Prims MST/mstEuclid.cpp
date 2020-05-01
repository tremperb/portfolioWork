/* Name: Brayden Tremper 
 * Email: tremperb@oregonstate.edu
 * Course: CS325 - Analysis of Algorithms
 * Description: Euclidian MST using prims algorithm
 * Date: 2/21/2020
 */

/* Read in our header files */
#include "point.h"
#include "node.h"
#include "graph.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>


using namespace std;


/*
 * This function read the data in from the given data.txt file 
 * and then stores it in a 2d vector.
 */
vector <vector <int> > read_text(int &vertices, char* file) {
    ifstream rf;
    
	rf.open(file);    //open our file
    if(rf.good() != true) { 
		cout << "Error!" << endl;   //if unsuccessful, quit
        exit(0);
	}
    
    int x, y;
    vector <vector <int> > coordinates;
    vector <int> X;
    vector <int> Y;
    rf >> vertices;

    while(!rf.eof()) {
        rf >> x;
        rf >> y;
        X.push_back(x);
        Y.push_back(y);
    } 
    coordinates.push_back(X);
    coordinates.push_back(Y);
   
    rf.close(); //close our file

    return coordinates;
}

/*
 * Our main function initializes some vlues and calls other functions
 */
int main(int argc, char**argv) {
    Point **p;
    int V = 0;
    
    if(argv[1] == NULL) {
        cout << "You must input your file as a command line argment" << endl;
        exit(0);
    }

    char* file = argv[1];
    cout <<"Your File: " << file << endl;
    vector <vector <int> > points = read_text(V, file);  //get our 2d vector from previous function
    vector <int> x = points[0];
    vector <int> y = points[1];
    p=new Point*[V];
    Graph graph(V);
    for(int i=0; i < V; i++) {
        p[i] = new Point(x[i], y[i]); //now we have x,y initialize our point
        Node n(i, p[i]);  //now that we have a point we have created a node so store it with id i
        graph.setNode(n);   //bring that node to our graph
    }
    
    graph.setGraph();   //initialize our graph
	graph.primMST();    //call our mst function
    return 0;
}