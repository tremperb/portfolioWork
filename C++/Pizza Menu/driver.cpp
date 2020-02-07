/******************************************************
** Program: driver.cpp - Pizza Portal
** Author: Brayden Tremper
** Date: 04/30/2019
** Description:
** Input: This prgram takes in various user inputs based
		  on the pizza they want to find or option to view.
** Output: This program outputs the information to the screen
		   as the user requests. Also, if an item is updated 
		   it is updated in the corresponding textfile.
******************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "pizza.h"
#include "menu.h"
#include "restaurant.h"
#include "Header.h"

using namespace std;

/*********************************************************************
** Function: main
** Description: calls display intro
** Parameters:na
** Pre-Conditions: all functions filled and textfiles present.
** Post-Conditions: program ends.
*********************************************************************/
int main() {
	display_intro();
//	system("pause");
	return 0;
}
