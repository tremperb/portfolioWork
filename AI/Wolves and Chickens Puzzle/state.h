#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class State {
private:
    vector <vector <int> > state; //the animal and boat info in 2d vector
    State* parent; //the parent
    int depth; //the depth from start
    //Starting at right going to left
public:
    State();
    State(vector <int> newState);
    vector < vector <int> > getState();
    void setParent(State* parent);
    State* getParent();
    void setDepth(int depth);
    int getDepth();
    ///////////////////
    void copy(State *higher);
    void moveBoat(int currentBank);
    void moveChickens(int currentBank);
    void moveWolves(int currentBank);
    int getLocation(int x, int y);
};
#endif