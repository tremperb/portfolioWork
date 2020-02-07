#include "pit.h"


/*********************************************************************
** Function: Pit
** Description: default constructor
*********************************************************************/
Pit::Pit()
{
}

/*********************************************************************
** Function: ~Pit
** Description: default destructor
*********************************************************************/
Pit::~Pit()
{
}

/*********************************************************************
** Function: encounter
** Description: get message for encounter and return its type 
*********************************************************************/
int Pit::encounter() {
	cout << "You have fallen into a bottomless pit!" << endl;
	return 1;
}

/*********************************************************************
** Function: percept
** Description: displays the percept
*********************************************************************/
void Pit::percept() {
	cout << "You feel a breeze" << endl;
}