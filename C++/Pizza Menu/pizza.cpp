/*Pizza.cpp - class*/

#include <iostream>
#include <string>
#include <fstream>
#include "pizza.h"

using namespace std;

/*********************************************************************
** Function: pizza
** Description: constructor initializes value
*********************************************************************/
Pizza::Pizza() {
	name = "N/A";
	small_cost = 0;
	medium_cost = 0;
	large_cost = 0;
	num_ingredients = 0;
	ingredients = NULL;
}

/*********************************************************************
** Function: ~Pizza
** Description: deletes allocated memory
*********************************************************************/
Pizza::~Pizza() {
	if (ingredients != NULL)
		delete[] ingredients;
}

/*********************************************************************
** Function: pizza
** Description: copies pizza
*********************************************************************/
Pizza::Pizza(const Pizza& pie) {
	this->name = pie.name;
	this->small_cost = pie.small_cost;
	this->medium_cost = pie.medium_cost;	//copies it to copy variable for everything
	this->large_cost = pie.large_cost;
	this->num_ingredients = pie.num_ingredients;
	if (num_ingredients == 0)
		ingredients = NULL;
	else {
		for (int i = 0; i < this->num_ingredients; i++) {
			this->ingredients[i] = pie.ingredients[i];
		}
	}
};

/*********************************************************************
** Function: pizza operator
** Description: allows copier to be used
*********************************************************************/
Pizza & Pizza::operator=(const Pizza & pie) {
	this->name = pie.name;
	this->small_cost = pie.small_cost;
	this->medium_cost = pie.medium_cost;
	this->large_cost = pie.large_cost;
	this->num_ingredients = pie.num_ingredients;
	if (ingredients != NULL)
		delete[] ingredients;

	this->ingredients = new string[this->num_ingredients];
	if (num_ingredients == 0)
		ingredients = NULL;
	else {
		for (int i = 0; i < num_ingredients; i++) {
			this->ingredients[i] = pie.ingredients[i];
		}
	}
	return *this;
}

/*********************************************************************
** Function: set name
** Description: allows access to private variable
*********************************************************************/
void Pizza::set_name(const string &name) {
	this->name = name;
}

/*********************************************************************
** Function: get name
** Description: gets variable
*********************************************************************/
string Pizza::get_name( ) const{
	return name;
}

/*********************************************************************
** Function: set_num_ingredients
** Description: allows access to private variable
*********************************************************************/
void Pizza::set_num_ingredients(const int &num) {
	num_ingredients = num;
}

/*********************************************************************
** Function: getnum ingredients
** Description: gets variable
*********************************************************************/
int Pizza::get_num_ingredients() const{
	return num_ingredients;
}
/*********************************************************************
** Function: get ingredients
** Description: gets variable
*********************************************************************/
string* Pizza::get_ingredients()const {
	return ingredients;
}

/*********************************************************************
** Function: set small cost
** Description: allows access to private variable
*********************************************************************/
void Pizza::set_small_cost(const int &cost) {
	small_cost = cost;
}

/*********************************************************************
** Function: get small cost
** Description: gets variable
*********************************************************************/
int Pizza::get_small_cost()const {
	return small_cost;
}

/*********************************************************************
** Function: set medium cost
** Description: allows access to private variable
*********************************************************************/
void Pizza::set_medium_cost(const int &cost) {
	medium_cost = cost;
}

/*********************************************************************
** Function: get medium cost
** Description: gets variable
*********************************************************************/
int Pizza::get_medium_cost()const {
	return medium_cost;
}

/*********************************************************************
** Function: set large cost
** Description: allows access to private variable
*********************************************************************/
void Pizza::set_large_cost(const int &cost) {
	large_cost = cost;
}

/*********************************************************************
** Function: get large cost
** Description: gets variable
*********************************************************************/
int Pizza::get_large_cost()const {
	return large_cost;
}

void Pizza::set_ingredients_array(const int &num) {
	ingredients = new string[num];
}

/*********************************************************************
** Function: fill ingredients array
** Description: fills the array of ingredients from temporary variable
*********************************************************************/
void Pizza::fill_ingredients_array(const int num, string temp[]) {
	for(int i=0; i < num; i++) {
		ingredients[i] = temp[i];
	}
}
