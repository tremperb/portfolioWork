/******************************************************
** Program: meerkat.cpp
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: defines meerkat class inheriting from animal
******************************************************/
#include "meerkat.h"

using namespace std;

/*********************************************************************
** Function: meerkat
** Description: default constructor
*********************************************************************/
Meerkat::Meerkat() {

}

/*********************************************************************
** Function: meerkat
** Description: non default constructor
*********************************************************************/
Meerkat::Meerkat(int age) : Animal(age, 500, 5, 1, 25) { //age, cost, babies, food multiplier, revenue

}

/*********************************************************************
** Function: ~meerkat
** Description: destructor
*********************************************************************/
Meerkat::~Meerkat() {
	//delete monkey array here once created
}

/*********************************************************************
** Function: meerkat
** Description: copier
*********************************************************************/
Meerkat::Meerkat(const Meerkat& Copy) : Animal(Copy) {
	cout << "Copy constructor called!" << endl;
}

/*********************************************************************
** Function: meerkat&operator
** Description: operator for = allowing for copies
*********************************************************************/
Meerkat & Meerkat::operator =(const Meerkat &Copy) {
	Animal::operator = (Copy);

	return *this;
}
