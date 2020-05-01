#ifndef HEURISTIC_H
#define HEURISTIC_H


#include <iostream>
#include "state.h"

class Heuristic {
private:
    int priority; //Priority for heuristic
    State* state; //The state it hlds
    
public:
    Heuristic();
    void setPriority(int priority);
    int getPriority();
    void setState(State* state);
    State* getState();
    int calculatePriority(State* goal);
    bool operator<(const Heuristic& h) const; //Operator overload for p_queue 

};
#endif