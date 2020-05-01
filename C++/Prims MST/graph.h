#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "node.h"
#include "point.h"

using namespace std;

class Graph {
private:
    Node *node;
    int **distance;
    int V;
    int idx;

public: 
    Graph();

    Graph(int V);

    void setNode(Node node);

    Node getNode(int in);

    int getDistance(Point *a, Point *b);

    void setGraph();

    int extractMin(vector <int> key, vector <bool> set);

    void printGraph(vector <int> p);

    void primMST();
    
};

#endif