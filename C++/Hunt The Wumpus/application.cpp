/*********************************************************************
** Program Filename: application.cpp (Hunt the Wumpus)
** Author: Brayden Tremper
** Date: 5/26/2019
** Description: This game displays a map which the player must interact with.
the player will move accordingly in order to get the gold and possibly kill the
wumpus and then reach the escape point. There is multiple special events that the user will 
have to navigate through.
** Input: various inputs for player direction or action
** Output: interactive grid to screen
*********************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include "room.h"

using namespace std;

/******************************************************************
** Function: check_size
** Description: checks to be sure size is >= 4
******************************************************************/
int check_size(int &size) {
	int error = 0;
	do{
		cout << "Enter your size: ";
		cin >> size;
		if(size >= 4)
			error = 0;
		else {
			cout << "Not valid, try again" << endl;
			error = 1;
		}
	}while(error == 1);

	return size;
}

/*********************************************************************
** Function: main
** Description: calls function to play game
*********************************************************************/
int main(int argc, char** argv) {
	string size_s = argv[1];	//accept as command line
	string old_debug = argv[2];	//accept as command line
	int size = atoi(size_s.c_str());
	string debug = old_debug;
	if(size < 4) {
		cout << "Not valid size!" << endl;
		size = check_size(size);
	}

	Room r1;
	r1.set_debug(debug);
	r1.play_game(size);
	
	return 0;
}
