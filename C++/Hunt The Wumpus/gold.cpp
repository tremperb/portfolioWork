#include "gold.h"
#include <iostream>

using namespace std;

/*********************************************************************
** Function: Gold
** Description: default constructor
*********************************************************************/
Gold::Gold() {
	
}

/*********************************************************************
** Function: ~Gold
** Description: default destructor
*********************************************************************/
Gold::~Gold() {

}

/*********************************************************************
** Function: encounter
** Description: get message for encounter and return its type (i use 1 for gold)
*********************************************************************/
int Gold::encounter() {
	cout << "You have found the gold!" << endl;
	return 2;
}

/*********************************************************************
** Function: percept
** Description: displays the percept
*********************************************************************/
void Gold::percept() {
	cout << "You see a glimmer nearby" << endl;
}
