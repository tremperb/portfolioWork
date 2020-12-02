/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

#define MAX_VAL -9999
#define MIN_VAL 9999

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

/**
 * This is my get move function which starts the 
 * AI process depending on the player of the AI.
 */
void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    // To be filled in by you
	
	/*Initialize varibles*/
	int max = MAX_VAL; 
	int min = MIN_VAL;
	int finalSuccessor = 0;
	int val = 0;

	/*
	* Get our possible successors states according 
	* to the player selected and store in vector
	*/
	vector <OthelloBoard*> successors = successorFunction(*b, get_symbol()); 


	for(int i =0; i < successors.size(); i++) { //Go through all possible successors
		if(get_symbol() == b->get_p1_symbol()) { //If the AI is player one
			val = min_value(*(successors[i]));

			//This is our maximizing player so compare against max
			if(val < max) {
				max = val; //update new max
				finalSuccessor = i; //Initialize successor to continue holder the index of best
			}
		}
		else {	//If the AI is player 2 
			val = max_value(*(successors[i])); //then it is our max

			//This is our minimizing player
			if(val < min) {
				min = val; //update new min
				finalSuccessor = i;
			}
		}
		
	}
	
	//This gets the rows and cols of our move for the best successor
	successors[finalSuccessor]->get_move_position(row, col);
	//Now finished make the move

	//Remove successor states so no memory leaks
	for(int i =0; i < successors.size(); i++) {
		delete successors[i];
	}
	
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}

/**
 * Simple min function returns smaller value
 */
int MinimaxPlayer::min(int a, int b) {
	if(a <= b) {
		return a;
	}
	else {
		return b;
	}
}

/**
 * Simple max function returns bigger value
 */
int MinimaxPlayer::max(int a, int b) {
	if(a >= b) {
		return a;
	}
	else {
		return b;
	}
}

/**
 * This is our minimizing function
 * It returns our minvalue
 * Reference: Pseudocode, Adversial Lecture slide 22
 */
int MinimaxPlayer::min_value(OthelloBoard board) {

	//Check if at terminal state aka either can make a move
	//Just like pseudo code return utility function if no moves
	if(!board.has_legal_moves_remaining(board.get_p1_symbol()) && !board.has_legal_moves_remaining(board.get_p2_symbol())) {
		return utilityFunction(board);
	}

	//get our successors for player 2 since its minimizing
	vector <OthelloBoard*> successors = successorFunction(board, board.get_p2_symbol());

	//define infinite min
	int minValue = MIN_VAL;
	
	//For each action state
	for(int i=0; i < successors.size(); i++) {
		minValue = min(minValue, max_value(*(successors[i]))); //find the actual min and update
	}

	//remove successor states
	for(int i=0; i < successors.size(); i++) {
		delete successors[i];
	}

	return minValue;
}


/**
 * This is our maximizing function
 * It returns our maxvalue
 * Reference: Pseudo code, Adversial Lecture slide 22
 */
int MinimaxPlayer::max_value(OthelloBoard board) {

	//Check if at terminal state aka either can make a move
	//Just like pseudo code return utility function if no moves
	if(!board.has_legal_moves_remaining(board.get_p1_symbol()) && !board.has_legal_moves_remaining(board.get_p2_symbol())) {
		return utilityFunction(board);
	}

	//get successors for player 1 since maximizing func.
	vector <OthelloBoard*> successors = successorFunction(board, board.get_p1_symbol());

	//define infinite max
	int maxValue = MAX_VAL;
	
	//For each action state
	for(int i = 0; i < successors.size(); i++) {
		maxValue = max(maxValue, min_value(*(successors[i]))); // find the actual max and update
	}

	//Remove successor states
	for(int i=0; i < successors.size(); i++) {
		delete successors[i];
	}

	return maxValue;
}

/**
 * This is the utility function which 
 * is used to determine how good the state is.
 */
int MinimaxPlayer::utilityFunction(OthelloBoard board) {

	//This will be the dirrence in scores to determine which player is doing better
	//With this it can determine the "goodness" of that state
	int result = board.count_score(board.get_p1_symbol()) - board.count_score(board.get_p2_symbol());

	return result;
}

/**
 * This is the successor function
 * It takes in the current board and the player it is analyzing
 * It then returns all possible successors stored in a vector
 */
vector <OthelloBoard*> MinimaxPlayer::successorFunction(OthelloBoard board, char playerID) {
	vector <OthelloBoard*> successors; //Initialize our vector to be used
	
	for(int i=0; i < board.get_num_rows(); i++) { //for each row
		for(int k=0; k < board.get_num_cols(); k++) {	//go through each column

			//If the move to that position is legal according to already defined rules
			if(board.is_legal_move(k, i, playerID)) {
				//Lets create a temp board to hold our new state setting it to the previous board set.
				OthelloBoard* tempBoard = new OthelloBoard(board);
				//Now make the move and store the position so it can be used later
				tempBoard->play_move(k, i, playerID);

				//Now take that possible state and store it
				successors.push_back(tempBoard);
				
			}

		}
	}

	return successors; // return the vector containg all possible values
}

