/******************************************************
** Program: monkey.cpp
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: defines monkey class inheriting from animal
******************************************************/
#include "monkey.h"
#include <ctime>

using namespace std;

/*********************************************************************
** Function: monkey
** Description: default constructor
*********************************************************************/
Monkey::Monkey(){
	
}

/*********************************************************************
** Function: monkey
** Description: non default constructor
*********************************************************************/
Monkey::Monkey(int age) : Animal(age, 15000, 1, 4, 1500) { //age, cost, babies,  food multiplier, revenue
	
}

/*********************************************************************
** Function: ~monkey
** Description: destructor
*********************************************************************/
Monkey::~Monkey() {
	//dont need 
}

/*********************************************************************
** Function: monkey
** Description: copier
*********************************************************************/
Monkey::Monkey(const Monkey& Copy) : Animal(Copy) {
}

/*********************************************************************
** Function: monkey&operator
** Description: operator for = allowing for copies
*********************************************************************/
Monkey & Monkey::operator =(const Monkey &Copy) {
	Animal::operator =(Copy);

	return *this;
}


