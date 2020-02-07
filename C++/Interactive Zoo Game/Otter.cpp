/******************************************************
** Program: otter.cpp
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: defines otter class inheriting from animal
******************************************************/

#include "otter.h"

using namespace std;

/*********************************************************************
** Function: otter
** Description: default constructor
*********************************************************************/
Otter::Otter() {

}

/*********************************************************************
** Function: otter
** Description: non default constructor
*********************************************************************/
Otter::Otter(int age) : Animal(age, 5000, 2, 1, 250) { //age, babies, cost, food multiplier, revenue
}

/*********************************************************************
** Function: ~otter
** Description: destructor
*********************************************************************/
Otter::~Otter() {
	//dont need to delete
}

/*********************************************************************
** Function: otter
** Description: copier
*********************************************************************/
Otter::Otter(const Otter& Copy) : Animal(Copy) {
}

/*********************************************************************
** Function: otter&operator
** Description: operator for = allowing for copies
*********************************************************************/
Otter & Otter::operator =(const Otter &Copy) {
	Animal::operator = (Copy);

	return *this;
}
