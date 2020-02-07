#include "bats.h"

/*********************************************************************
** Function: Bats
** Description: default constructor
*********************************************************************/
Bats::Bats()
{
}

/*********************************************************************
** Function: ~Bats
** Description: default destructor
*********************************************************************/
Bats::~Bats()
{
}

/*********************************************************************
** Function: encounter
** Description: get message for encounter and return its type
*********************************************************************/
int Bats::encounter() {
	cout << "You have encountered super bats!" << endl;
	cout << "They have picked you up and dropped you at a random point!" << endl;
	return 3;
}

/*********************************************************************
** Function: percept
** Description: displays the percept
*********************************************************************/
void Bats::percept() {
	cout << "You hear wings flapping" << endl;
}