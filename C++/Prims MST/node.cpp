/* This is our node class
 * The node class stores the specific point and the id to locate that point
 * as illustrated by the mst we have been viewing.
 * 
 */

#include "node.h"
#include <iostream>
using namespace std;

Node::Node() {} //default constructor wont be called 

Node::Node(int id, Point*p) { //alternatate constructor will be called 
    this->id=id;
    this->p=p;
}

void Node::setID(int id) { //setter for id
    this->id=id;
}

void Node::setP(Point*p) { //setter for point
    this->p=p;
}

int Node::getID() {     //getter for id
    return id;
}

Point *Node::getP() { //getter for point
    return p;
}