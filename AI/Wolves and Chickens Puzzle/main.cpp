/* Brayden Tremper */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <stack>
#include <list>
#include <queue>

#include "state.h"
#include "heuristic.h"

using namespace std;

/***************************************
 *             READ FILE
 * ************************************/
vector <int> openFile(char* file) {

    vector <int> Bank;
    ifstream rf;
    rf.open(file);
    string holder;
    string temp;
    while(getline(rf, holder)) {
        stringstream ss(holder);
        while(getline(ss, temp, ',')) {
            Bank.push_back(atoi(temp.c_str()));
        }
    }
    rf.close();

    return Bank;
}

/***************************************
 *               CHECK IT DOESN'T BREAK RULES
 * ************************************/
bool checkWolvesDontEatChickens(State* state) {
    int chickensRight = state->getLocation(0,0);
    int wolvesRight = state->getLocation(0, 1);
    int chickensLeft = state->getLocation(1, 0);
    int wolvesLeft = state->getLocation(1, 1);
    if(chickensRight < wolvesRight && chickensRight != 0) {
        return false;
    }
    if(chickensLeft < wolvesLeft && chickensLeft != 0) {
        return false;
    }

    //Otherwise the chickens wont be outnumbered and eaten
    return true;
}

/***************************************
 *               SUCCESSORS
 * ************************************/
void findSuccessor(State *state, vector <State*> *successors) {
    int boatSide = state->getLocation(1, 2);
    
    //Gets the current boat side if left it should return 1

    /*  Put one chicken in the boat
        Put two chickens in the boat
        Put one wolf in the boat
        Put one wolf and one chicken in the boat
        Put two wolves in the boat */
    
    if(state->getLocation(boatSide, 0) >= 1) {
        //put one chicken on boat
        State *newState = new State;
        newState->copy(state);
        newState->moveChickens(boatSide);
        newState->moveBoat(boatSide);

        if(checkWolvesDontEatChickens(newState)) {
            successors->push_back(newState);
            
        }
        else {
            //Not valid disregard state
            delete newState;
        }
        
    }
    if(state->getLocation(boatSide, 0) >= 2) {
        //put two chickens on boat
        State *newState = new State;
        newState->copy(state);
        newState->moveChickens(boatSide);
        newState->moveChickens(boatSide);
        newState->moveBoat(boatSide);

        if(checkWolvesDontEatChickens(newState)) {
            successors->push_back(newState);
            
        }
        else {
            //Not valid disregard state
            delete newState;
        }
    }
    if(state->getLocation(boatSide, 1) >= 1) {
        //put one wolf on boat
        State *newState = new State;
        newState->copy(state);
        newState->moveWolves(boatSide);
        newState->moveBoat(boatSide);

        if(checkWolvesDontEatChickens(newState)) {
            successors->push_back(newState);
            
        }
        else {
            //Not valid disregard state
            delete newState;
        }
    }
    if(state->getLocation(boatSide, 0) >= 1 && state->getLocation(boatSide, 1) >= 1) {
        //put one wolf and one chicken on boat
        State *newState = new State;
        newState->copy(state);
        newState->moveChickens(boatSide);
        newState->moveWolves(boatSide);
        newState->moveBoat(boatSide);

        if(checkWolvesDontEatChickens(newState)) {
            successors->push_back(newState);
            
        }
        else {
            //Not valid disregard state
            delete newState;
        }
    }
    if(state->getLocation(boatSide, 1) >= 2) {
        //put two wolves on boat
        State *newState = new State;
        newState->copy(state);
        newState->moveWolves(boatSide);
        newState->moveWolves(boatSide);
        newState->moveBoat(boatSide);

        if(checkWolvesDontEatChickens(newState)) {
            successors->push_back(newState);
            
        }
        else {
            //Not valid disregard state
            delete newState;
        }
    }

}

/*
 General equal checker
 Takes in 2 states and gets the location info from each
 if all are equal then the two statess are equal
 */
bool checkEqual(State* one, State* two) {
    bool good = false;
    int c1r1 = one->getLocation(0, 0);
    int c2r1 = two->getLocation(0, 0);
    int w1r1 = one->getLocation(0, 1);
    int w2r1 = two->getLocation(0, 1);
    int b1r1 = one->getLocation(0, 2);
    int b2r1 = two->getLocation(0, 2);
    /////////////////////////////////
    int c1r2 = one->getLocation(1, 0);
    int c2r2 = two->getLocation(1, 0);
    int w1r2 = one->getLocation(1, 1);
    int w2r2 = two->getLocation(1, 1);
    int b1r2 = one->getLocation(1, 2);
    int b2r2 = two->getLocation(1, 2);
    
    if((c1r1 == c2r1) && (w1r1 == w2r1) && (b1r1 == b2r1)
    && (c1r2 == c2r2) && (w1r2 == w2r2) && (b1r2 == b2r2)) {
            return true;
    }
    else {
        return false;
    }
}

/***************************************
 *               CHECK VISITED
 * ************************************/
bool checkVisited(vector <State*> visitedStates, State* current) {
    bool good = true;
    for(int i=0; i < visitedStates.size(); i++) { //going through check if equal to one already visited
        if(checkEqual(visitedStates[i], current)) {
            return true;
        }
    }

    return false;

}


/***************************************
 *              PRINTING
 * ************************************/
void printPath(State *currState, int nodesExpanded, char *file, string algType) {
    ofstream wf;
    wf.open(file);
    
    vector <State*> path;

    path.push_back(currState);
    while(true) {
        if(currState->getParent() != NULL) {
            currState = currState->getParent();
            path.push_back(currState);
        }
        else {
            break;
        }
    }

    cout << "Selected Algorithm: " << algType << endl;
    cout << endl;
    wf << "Selected Algorithm: " << algType << endl;
    wf << endl;
    //Go backwards since the end is our start state
    for(int i=path.size()-1; i >= 0; i--) {
        cout << path[i]->getLocation(0, 0) << " " << path[i]->getLocation(0, 1) << " " << path[i]->getLocation(0, 2) << endl;
        cout << path[i]->getLocation(1, 0) << " " << path[i]->getLocation(1, 1) << " " << path[i]->getLocation(1, 2) << endl;
        cout << endl;

        wf << path[i]->getLocation(0, 0) << " " << path[i]->getLocation(0, 1) << " " << path[i]->getLocation(0, 2) << endl;
        wf << path[i]->getLocation(1, 0) << " " << path[i]->getLocation(1, 1) << " " << path[i]->getLocation(1, 2) << endl;
        wf << endl;
    }
    
    wf << "Total Nodes: " << path.size() << endl;
    wf << "Nodes expanded: " << nodesExpanded << endl;

    cout << "Total Nodes: " << path.size() << endl;
    cout << "Nodes expanded: " << nodesExpanded << endl;

    wf.close();
}


/***************************************
 *          START ALGORITHMS
 * ************************************/


/***************************************
 *               BFS
 * ************************************/
void BFS(State *startState, State *goalState, char* file) {
    
    list <State*> list; //list full of states to hold state path
    vector <State*> visitedStates;
    vector <State*> successors;
    int nodesExpanded = 0;
    bool goalFound = false;
    State *temp;
    State *checkSuccessor;

    list.push_back(startState);

    while(!list.empty()) {
        temp = list.front();
        list.pop_front();
        
        if(checkEqual(temp, goalState)) {
            printPath(temp, nodesExpanded, file, "Breadth First Search");
            goalFound = true;

        }
        else {
           
            //like getting the adjacent vertices but succssor posibilities
            findSuccessor(temp, &successors); //so given our current find all possible successors
            while(!successors.empty()) { // now go through to find which
                checkSuccessor = successors.back(); //starting from last in vector
                successors.pop_back();

                if(!checkVisited(visitedStates, checkSuccessor)) { //only if we havent visited it
                    visitedStates.push_back(checkSuccessor); //good so do that move
                    checkSuccessor->setParent(temp); //reinitialize parent for new added state
                    list.push_back(checkSuccessor); //now put the successor into our path
                    
                }
                else {
                    delete checkSuccessor;
                    
                }
            }
            nodesExpanded++;
            
             
        }
    }
    if(!goalFound) {
        cout << "No solution found" << endl;
    }
}

//DFS and BFS are similar really only need the way things are stored to affect the order they operate
/***************************************
 *               DFS
 * ************************************/
void DFS(State *startState, State *goalState, char* file) {
    
    stack <State*> stack; //use stack since dFS
    vector <State*> visitedStates;
    vector <State*> successors;
    int nodesExpanded = 0;
    bool goalFound = false;
    State *temp;
    State *checkSuccessor;

    stack.push(startState);

    while(!stack.empty()) {
        temp = stack.top();
        stack.pop();
        
        if(checkEqual(temp, goalState)) {
            printPath(temp, nodesExpanded, file, "Depth First Search");
            goalFound = true;

        }
        else {
           
            //like getting the adjacent vertices but succssor posibilities
            findSuccessor(temp, &successors); //so given our current find all possible successors
            while(!successors.empty()) { // now go through to find which
                checkSuccessor = successors.back(); //starting from last in vector
                successors.pop_back();

                if(!checkVisited(visitedStates, checkSuccessor)) { //only if we havent visited it
                    visitedStates.push_back(checkSuccessor); //good so do that move
                    checkSuccessor->setParent(temp); //reinitialize parent for new added state
                    stack.push(checkSuccessor); //now put the successor into our path
                    
                }
                else {
                    delete checkSuccessor;
                    
                }
            }
            nodesExpanded++; //increase nodes expanded
            
             
        }
    }
    if(!goalFound) {
        cout << "No solution found" << endl;
    }
}


/***************************************
 *               IDDFS
 * ************************************/
void IDDFS(State* startState, State* goalState, char* file) {
    stack <State*> stack;
    vector <State*> visitedStates;
    vector <State*> successors;
    int nodesExpanded;
    bool goalFound = false;
    State *temp;
    State *checkSuccessor;

    int maxDepth = 0;
    
    while(true) {
        int newDeepest = 0;
        stack.push(startState);

        while(!stack.empty()) {
            temp = stack.top();
            stack.pop();
            if(newDeepest < temp->getDepth()) {
                newDeepest = temp->getDepth();
            }

            if(checkEqual(temp, goalState)) {
                printPath(temp, nodesExpanded, file, "Iterative Deepening Depth First Search");
                goalFound = true;
                break;
            }
            else if(temp->getDepth() <= maxDepth) {
           
                //like getting the adjacent vertices but succssor posibilities
                findSuccessor(temp, &successors); //so given our current find all possible successors
                while(!successors.empty()) { // now go through to find which
                    checkSuccessor = successors.back(); //starting from last in vector
                    successors.pop_back();

                    if(!checkVisited(visitedStates, checkSuccessor)) { //only if we havent visited it
                        visitedStates.push_back(checkSuccessor); //good so do that move
                        checkSuccessor->setParent(temp); //reinitialize parent for new added state
                        stack.push(checkSuccessor); //now put the successor into our path
                    
                    }
                    else {
                        delete checkSuccessor;
                    
                    }
                }
                nodesExpanded++;
            
            }
        }
        if(goalFound) {
            break;
        }
        if(newDeepest < maxDepth) { //no solution
            break;
        }
        
        maxDepth++;
        visitedStates.clear();
    }
    
    if(!goalFound) {
        cout << "No solution found" << endl;
    }
}

/***************************************
 *               ASTAR
 * ************************************/
void astar(State* startState, State* goalState, char* file) {
    Heuristic h;

    priority_queue <Heuristic> p_queue;
    vector <State*> visitedStates;

    h.setState(startState);
    h.setPriority(h.calculatePriority(goalState));
    //abs(goal sum - start sum);
    p_queue.push(h);
    //stack <State*> stack;
    
    vector <State*> successors;
    int nodesExpanded = 0;
    bool goalFound = false;
    Heuristic tempH;
    State *temp;
    State *checkSuccessor;

    while(!p_queue.empty()) {
        tempH = p_queue.top();
        temp = tempH.getState();
        p_queue.pop();
        
        if(checkEqual(temp, goalState)) {
            printPath(temp, nodesExpanded, file, "A-Star Search");
            goalFound = true;
        }
        else {
           
            //like getting the adjacent vertices but succssor posibilities
            findSuccessor(temp, &successors); //so given our current find all possible successors
            while(!successors.empty()) { // now go through to find which
                checkSuccessor = successors.back(); //starting from last in vector
                successors.pop_back();

                if(!checkVisited(visitedStates, checkSuccessor)) { //only if we havent visited it
                    visitedStates.push_back(checkSuccessor); //good so do that move
                    checkSuccessor->setParent(temp); //reinitialize parent for new added state

                    Heuristic newh;
                    newh.setState(checkSuccessor);
                    newh.setPriority(h.calculatePriority(goalState));
                    p_queue.push(newh); //now put the successor into our path
                    
                }
                else {
                    delete checkSuccessor;
                    
                }
            }
            nodesExpanded++;
            
             
        }
    }
    if(!goalFound) {
        cout << "No solution found" << endl;
    }
}

/***************************************
 *               MAIN
 * ************************************/

int main(int argc, char* argv[]) {
    //< initial state file > < goal state file > < mode > < output file >
    if(argc != 5) {
        cout << "Invalid, follow format: < initial state file > < goal state file > < mode > < output file > " << endl;
        exit(0);
    }
    //char *initialState = argv[1];
    
    string mode = string(argv[3]);
    char *outputFile=argv[4];

    vector <int> initial = openFile(argv[1]);
    vector <int> goal = openFile(argv[2]);
    State *initialState = new State(initial);
    State *goalState = new State(goal);
    

    if(mode == "bfs"){
        BFS(initialState, goalState, argv[4]);
    }
    else if(mode == "dfs") {
        DFS(initialState, goalState, argv[4]);
    }
    else if(mode == "iddfs"){
        IDDFS(initialState, goalState, argv[4]);
    }
    else if(mode == "astar") {
        astar(initialState, goalState, argv[4]);
    }
    else {
        cout << "Not a valid mode" << endl;
        exit(0);
    }
    
    return 0;
}