#ifndef RESTAURANT
#define RESTAURANT

#include <iostream>
#include <string>
#include "menu.h"
#include "Header.h"

using namespace std;

class Restaurant {
private:
	Menu menu;
	employee* employees;
	hours* week;
	string name;
	string phone;
	string address;
public:
	//need to include accessor functions and mutator functions for each private member
	//need to include constructors, copy constructors, assignment operator overload,
	//and destructors where appropriate
	Restaurant();
	~Restaurant();
	Restaurant(const Restaurant& copy);
	Restaurant& operator = (const Restaurant& copy);
	void set_name(const string &name);
	string get_name() const;
	void set_phone(const string &phone);
	string get_phone() const;
	void set_address(const string &address);
	string get_address() const;
	int get_num_employees();
	employee* employee_array(int num_employees);
	void get_employees();
	string get_employee_id();
	string get_employee_password();
	void load_data(); //reads from files to correctly populate menu, employees, hours, etc.
	int login(string id, string password);
	void diplay_login();
	void view_menu();
	void view_hours();
	void view_address();
	void view_phone();
	string get_size();
	void search_menu_by_price();
	void search_by_ingredients();
	void change_hours();
	void view_orders();
	void remove_orders();
};
#endif

