/*
 *This is our point class functions
 *the purpose of this class is to take our x and y coordinates from our
 *vector and save the point in them so it can be accessed via our node class
 *to get the value such as node->p->getX()
 */ 
#include "point.h"

Point::Point() { //default just set to 0 
    x = 0;
    y = 0;
}

Point::Point(int x, int y) { //non -default constructor
    this->x = x;
    this->y = y;
}

void Point::setX(int x) { //setter for x coordinate
    this->x = x;
}

void Point::setY(int y) { //setter for y
    this->y = y;
}

int Point::getX() { //get our x coordinate
    return x;
}

int Point::getY() { //get our y coordinate
    return y;
}
