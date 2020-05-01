/* This is our node class
 * The node class stores the specific point and the id to locate that point
 * as illustrated by the mst we have been viewing.
 * 
 */

#include "bank.h"
#include <iostream>
using namespace std;

Bank::Bank() {} //default constructor wont be called 

void Bank::setChickens(int chickens) { //setter for id
    this->chickens=chickens;
}

int Bank::getChickens() {
    return chickens;
}

void Bank::setWolves(int wolves) { //setter for id
    this->wolves=wolves;
}

int Bank::getWolves() {
    return wolves;
}

void Bank::setBoat(int boat) { //setter for id
    this->boat=boat;
}

int Bank::getBoat() {
    return boat;
}