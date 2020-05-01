#include "state.h"
#include <cmath>

State::State() {} //wont get called

State::State(vector <int> newState) {
    //Initial lize 1d vector state and switch to 2d to be used as hash table
    vector <int> row(3); //initialize vector size
    state.push_back(row);
    for(int i=0; i < 3; i++) {
        state[0][i] = newState[i];
        //state[0].push_back(newState[i]);
    }
    
    state.push_back(row);
    int count = 3;
    for(int i=0; i < 3; i++) {
        state[1][i] = newState[count];
        count++;
    }
    
    parent = NULL;

}

vector < vector <int> > State::getState() {
    return state;
}

void State::setParent(State* parent) {
    this->parent = parent; //set the parent but one more so increasee depth too
    depth = this->parent->getDepth() + 1;
}

State* State::getParent(){
    return parent;
}

void State::setDepth(int depth) {
    this->depth = depth;
}

int State::getDepth() {
    return depth;
}
////////////////////////
///End mutator functions///
//////////////////////////
void State::copy(State *higher) {
    vector < vector <int> > higherTable = higher->getState();
    //just a simple copy algorithm
    vector <int> row(3);
    state.push_back(row);
    state.push_back(row);
    for(int i=0; i < 2; i++) {
        for(int k=0; k < 3; k++) {
            state[i][k] = higherTable[i][k];
        }
    }

    parent = higher->getParent();
    depth = higher->getDepth();

}

//Note if error try changing this?
void State::moveBoat(int currentBank) {
    //move boat to the other side based on where it currently is
    if(currentBank == 1) {
        state[1][2] = 0;
        state[0][2] = 1;
    }
    else {
        state[1][2] = 1;
        state[0][2] = 0;
    }

}

void State::moveChickens(int currentBank) {
    if(state[currentBank][0] != 0) { //if there is actually chickens to get
        state[currentBank][0]--; //take away one chicken
        if(currentBank == 1) {
            state[0][0]++; //put one more chicken on that side
        }
        else {
            state[1][0]++;
        }
    }
    else {
        cout << "No available chickens" << endl;
    }

}

void State::moveWolves(int currentBank) {
    if(state[currentBank][1] != 0) { //if there is actually wolvess to get
        state[currentBank][1]--;
        if(currentBank == 1) {
            state[0][1]++;
        }
        else {
            state[1][1]++;
        }
    }
    else {
        cout << "No available wolves" << endl;
    }

}

int State::getLocation(int x, int y) {
    return state[x][y]; //get value at given location
    /*
    R: [chickens][wolves][boat]
    L: [chickens][wolves][boat]
    */
}

