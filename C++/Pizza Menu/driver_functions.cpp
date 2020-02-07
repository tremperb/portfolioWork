#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "menu.h"
#include "restaurant.h"
#include "pizza.h"

using namespace std;

/*********************************************************************
** Function: display itro
** Description: displays intro asking user what type they are
*********************************************************************/
void display_intro() {
	string option;
	int error = 0;
	Restaurant r1;
	r1.load_data();
	do {
		error = 0;
		cout << "Welcome to Bytes Pizza!" << endl;
		cout << "Are you a customer(C), employee(E), or would you like to quit(Q)? ";
		cin >> option;
		if (option == "C" || option == "c")
			customer_options();
		else if (option == "E" || option == "e") {
			r1.diplay_login(); //requires login since employee
			employee_options();
		}
		else if (option == "Q" || option == "q")
			exit(0);
		else {
			cout << "Not valid, try again" << endl;
			error = 1;
		}
	} while (error == 1); // keep going til valid
}

/*********************************************************************
** Function: employee options
** Description: displays employee options
*********************************************************************/
void employee_options() {
	int x;
	int error = 0;
	Menu m1;
	do {
		do {
			error = 0;
			cout << endl;
			cout << "What would you like to do?" << endl;
			cout << "1. Change Hours" << endl;
			cout << "2. View Orders" << endl;
			cout << "3. Remove Order" << endl; //need
			cout << "4. Add item to menu" << endl;
			cout << "5. Remove item from menu" << endl;
			cout << "6. View Menu" << endl;
			cout << "7. View Hours" << endl;
			cout << "8. View Address" << endl;
			cout << "9. View Phone" << endl;
			cout << "10. Logout" << endl;
			cout << "Make a selection" << endl;
			x = m1.get_integer();
			if (x > 10) {
				cout << "Error, try again" << endl;
				error = 1;
			}
			cout << endl;
		} while (error == 1);

		employee_selection(x);
	} while (x != 10); //keep going til log off
}

/*********************************************************************
** Function: employee selection
** Description: calls function based on user desired option
*********************************************************************/
void employee_selection(int x) {

	switch (x) { //switch statements for all possible cases
		case 1: changeHours();
			break;	//breaks after called
		case 2: viewOrders();
			break;
		case 3: removeOrders();
			break;
		case 4: addMenuItem();
			break;
		case 5: removeMenuItem();
			break;
		case 6: viewMenu();
			break;
		case 7: viewHours();
			break;
		case 8: viewAddress();
			break;
		case 9: viewPhone();
			break;
		case 10: exit(0);
			break;
	}
}

/*********************************************************************
** Function: customer options
** Description: displays customer options
*********************************************************************/
void customer_options() {
	int selection;
	int error = 0;
	Menu m1;
	
	do {
		do {
			error = 0;
			cout << endl;
			cout << "What would you like to do?" << endl;
			cout << "1. View Menu" << endl;
			cout << "2. Search by Cost" << endl;
			cout << "3. Search by ingredients" << endl;
			cout << "4. Place Order" << endl;
			cout << "5. View Hours" << endl;
			cout << "6. View Address" << endl;
			cout << "7. View Phone" << endl;
			cout << "8. Logout" << endl;
			cout << "Make a selection" << endl;
			selection = m1.get_integer();
			if (selection > 8) {
				cout << "Error, try again" << endl;
				error = 1;
			}
			cout << endl;
		} while (error == 1);

	customer_selection(selection);
	} while (selection != 8); //keep going until log off
}

/*********************************************************************
** Function: customer selection
** Description: calls function based on user desired option
*********************************************************************/
void customer_selection(int x) {

	switch (x) { //switch statement for each option
	case 1: viewMenu();
		break;
	case 2: searchCost(); //calls function for corresponsding case
		break;				// breaks out of switch
	case 3: searchIngredients();
		break;
	case 4: placeOrder();
		break;
	case 5: viewHours();
		break;
	case 6: viewAddress();
		break;
	case 7: viewPhone();
		break;
	case 8: exit(0);
		break;
	}
}

/*********************************************************************
** Function: removeOrders
** Description: calls functions from class
*********************************************************************/
void removeOrders() {
	Restaurant r1;
	r1.remove_orders();
}

/*********************************************************************
** Function: viewPhone
** Description: calls functions from class
*********************************************************************/
void viewPhone() {
	Restaurant r1;
	r1.view_phone();
}

/*********************************************************************
** Function: ViewAddress
** Description: calls functions from class
*********************************************************************/
void viewAddress() {
	Restaurant r1;
	r1.view_address();
}

/*********************************************************************
** Function: viewHours
** Description: calls functions from class
*********************************************************************/
void viewHours() {
	Restaurant r1;
	r1.view_hours();
}

/*********************************************************************
** Function: placeOrder
** Description: calls functions from class
*********************************************************************/
void placeOrder() {
	Menu m1;
	m1.place_order();
}

/*********************************************************************
** Function: searchIngredients
** Description: calls functions from class
*********************************************************************/
void searchIngredients() {
	Restaurant r1;
	r1.search_by_ingredients();
}

/*********************************************************************
** Function: searchCost
** Description: calls functions from class
*********************************************************************/
void searchCost() {
	Restaurant r1;
	r1.search_menu_by_price();
}

/*********************************************************************
** Function: viewMenu
** Description: calls functions from class
*********************************************************************/
void viewMenu() {
	Restaurant r1;
	r1.view_menu();
}

/*********************************************************************
** Function: changeHours
** Description: calls functions from class
*********************************************************************/
void changeHours() {
	Restaurant r1;
	r1.change_hours();
}

/*********************************************************************
** Function: viewOrders
** Description: calls functions from class
*********************************************************************/
void viewOrders() {
	Restaurant r1;
	r1.view_orders();
}

/*********************************************************************
** Function: addMenuItem
** Description: calls functions from class
*********************************************************************/
void addMenuItem() {
	Menu m1;
	m1.get_add_to_menu();
}

/*********************************************************************
** Function: removeMenuItem
** Description: calls functions from class
*********************************************************************/
void removeMenuItem() {
	Menu m1;
	m1.get_pizza_remove();
}


