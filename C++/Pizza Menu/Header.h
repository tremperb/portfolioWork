#ifndef HEADER
#define HEADER

#include <iostream>

using namespace std;

struct employee {
	int id;
	string password;
	string first_name;
	string last_name;
};

struct hours {
	string day;
	string open_hour;
	string close_hour;
};



void display_intro();
void employee_options();
void employee_selection(int x);
void customer_selection(int selection);
void customer_options();
void removeOrders();
void viewPhone();
void viewAddress();
void viewHours();
void placeOrder();
void searchIngredients();
void searchCost();
void viewMenu();
void changeHours();
void viewOrders();
void addMenuItem();
void removeMenuItem();


#endif