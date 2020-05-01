#ifndef NODE_H
#define NODE_H

#include "point.h"
#include <iostream>


class Node {
private:
    int id;
    Point *p;
public:
    Node();
    Node(int id, Point*p);
    void setID(int id);
    void setP(Point*p);
    int getID();
    Point *getP();

};
#endif