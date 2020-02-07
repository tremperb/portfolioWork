/******************************************************
** Program: animal.cpp
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: defines animal class. Used as parent class
for all animals
******************************************************/
#include "animal.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

/*********************************************************************
** Function: animal
** Description: animal constructor, intializes starting values
*********************************************************************/
Animal::Animal() {
	age = -1;
	price = 0;
	num_babies = 0;
	food_cost = 0;
	revenue = 0;
}

/*********************************************************************
** Function: animal
** Description: animal non default constructor 
*********************************************************************/
Animal::Animal(int age, int price, int num_babies, int food_cost, int revenue) {
	this->age = age;
	this->price = price;
	this->num_babies = num_babies;
	this->food_cost = food_cost;
	this->revenue = revenue;
}

/*********************************************************************
** Function: animal
** Description: animal copier
*********************************************************************/
Animal::Animal(const Animal & Copy) {
	this->age = Copy.age;
	this->price = Copy.price;
	this->num_babies = Copy.num_babies;
	this->food_cost = Copy.food_cost;
	this->revenue = Copy.revenue;
}

/*********************************************************************
** Function: animal&operator
** Description: operator for = allowing for copies
*********************************************************************/
Animal & Animal::operator=(const Animal & Copy) {
	this->age = Copy.age;
	this->price = Copy.price;
	this->num_babies = Copy.num_babies;
	this->food_cost = Copy.food_cost;
	this->revenue = Copy.revenue;

	return *this;
}
/*********************************************************************
** Function: ~animal
** Description: delete memory
*********************************************************************/
Animal::~Animal() {
	//dont need to delete anything since allocated memory
	//is in zoo class
}

/*********************************************************************
** Function: get age
** Description: gets the value to be used
*********************************************************************/
int Animal::get_age() const{
	return age;
}

/*********************************************************************
** Function: get price
** Description: gets the value to be used
*********************************************************************/
int Animal::get_price() const {
	return price;
}

/*********************************************************************
** Function: get num babies
** Description: gets the value to be used
*********************************************************************/
int Animal::get_num_babies() const {
	return num_babies;
}

/*********************************************************************
** Function: get food cost
** Description: gets the value to be used
*********************************************************************/
int Animal::get_food_cost() const {
	return food_cost;
}

/*********************************************************************
** Function: get revenue
** Description: gets the value to be used
*********************************************************************/
int Animal::get_revenue() const {
	return revenue;
}



