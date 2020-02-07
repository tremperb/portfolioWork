#include "wumpus.h"

/*********************************************************************
** Function: encounter
** Description: get message for encounter and return its type
*********************************************************************/
int Wumpus::encounter() {
	cout << "You have wandered into the same room as the Wumpus!" << endl;
	return 1;
}

/*********************************************************************
** Function: percept
** Description: displays the percept
*********************************************************************/
void Wumpus::percept() {
	cout << "You smell a terrible stench" << endl;
}