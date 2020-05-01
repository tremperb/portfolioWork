#include "heuristic.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Heuristic::Heuristic() {} //default constructor wont be called 

void Heuristic::setPriority(int priority) { //setter for id
    this->priority=priority;
}

int Heuristic::getPriority() {
    return priority;
}

void Heuristic::setState(State* state) {
    this->state = state;
}

State* Heuristic::getState() {
    return state;
}

//Uses approximation heuristic to get value goal - currentsume
int Heuristic::calculatePriority(State* goal) {
    int goalSum, startSum, totalSum;
    goalSum = goal->getLocation(0, 0) + goal->getLocation(0, 1) + goal->getLocation(0, 2);
    startSum = state->getLocation(0, 0) + state->getLocation(0, 1) + state->getLocation(0, 2);
    
    totalSum = abs(goalSum - startSum);

    return totalSum;
}

bool Heuristic::operator<(const Heuristic& h) const {
    return priority >= h.priority;
}
