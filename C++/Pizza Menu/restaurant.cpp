#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "menu.h"
#include "restaurant.h"
#include "pizza.h"

using namespace std;

/*********************************************************************
** Function: restaurant
** Description: Restaurant constructor assigns standard variables
** Parameters: na
** Pre-Conditions: restaurant declared
** Post-Conditions: will be change
*********************************************************************/
Restaurant::Restaurant() {
	Menu menu;
	employees = NULL;
	week = NULL;
	name = "NA";
	phone = "(111) 222-3333";
	address = "1234 sw blah pl";  //all initialize standard variables
}

/*********************************************************************
** Function: ~Restaurant
** Description: deletes allocated memory
** Parameters: na
** Pre-Conditions: array is not NULL
** Post-Conditions: arrays need to be filled again
*********************************************************************/
Restaurant::~Restaurant() {
	if (employees != NULL) {
		delete[] this->employees; // deletes
	}
	if (week != NULL) {
		delete[] this->week; // deletes
	}
	employees = NULL;
	week = NULL;
}

/*********************************************************************
** Function: restaurant
** Description: makes a copy of restaurant
** Parameters: restaurant copy
** Pre-Conditions: restaurant declared
** Post-Conditions: copied value outputted
*********************************************************************/
Restaurant::Restaurant(const Restaurant& copy) {
	int num_employees = get_num_employees();
	this->menu = copy.menu; //copys each item
	this->name = copy.name;
	this->phone = copy.phone;
	this->address = copy.address;
	if (num_employees > 0) {
		for (int i = 0; i < num_employees; i++) {
			this->employees[i] = copy.employees[i];
		}
	}
	else
		this->employees = NULL;
	if (week != NULL) {
		for (int i = 0; i < 7; i++) {
			this->week[i] = copy.week[i];
		}
	}
}

/*********************************************************************
** Function: restaurant operator
** Description: restaurant operator allowing copies
** Parameters: restaurant copy
** Pre-Conditions: copy holds true
** Post-Conditions: copy to be used later on
*********************************************************************/
Restaurant & Restaurant::operator=(const Restaurant & copy) {
	int num_employees = get_num_employees();
	this->menu = copy.menu;
	this->name = copy.name;
	this->phone = copy.phone;
	this->address = copy.address;
	if (employees != NULL)
		delete[] employees;
	else {
		for (int i = 0; i < num_employees; i++) {
			this->employees[i] = copy.employees[i];
		}
	}
	if (week != NULL)
		delete[] this->week;
	else {
		for (int i = 0; i < 7; i++) {
			this->week[i] = copy.week[i];
		}
	}

	return *this;
}

/*********************************************************************
** Function: set_name
** Description: gets access to private variable
** Parameters: name
** Pre-Conditions: item declared in class
** Post-Conditions: inputted to get function to get access
*********************************************************************/
void Restaurant::set_name(const string &name) {
	this->name = name;
}

/*********************************************************************
** Function: get_name
** Description: gets access to private variable
** Parameters: na
** Pre-Conditions: item declared in class
** Post-Conditions: item is now accessible
*********************************************************************/
string Restaurant::get_name() const {
	return name;
}

/*********************************************************************
** Function: set_phone
** Description: gets access to private variable
** Parameters: phone
** Pre-Conditions: item declared in class
** Post-Conditions: inputted to get function to get access
*********************************************************************/
void Restaurant::set_phone(const string &phone) {
	this->phone;
}

/*********************************************************************
** Function: get_phone
** Description: gets access to private variable
** Parameters: na
** Pre-Conditions: item declared in class
** Post-Conditions: item is now accessible
*********************************************************************/
string Restaurant::get_phone() const {
	return phone;
}

/*********************************************************************
** Function: set_address
** Description: gets access to private variable
** Parameters: address
** Pre-Conditions: item declared in class
** Post-Conditions: inputted to get function to get access
*********************************************************************/
void Restaurant::set_address(const string &address) {
	this->address;
}

/*********************************************************************
** Function: get_address
** Description: gets access to private variable
** Parameters: na
** Pre-Conditions: item declared in class
** Post-Conditions: item is now accessible
*********************************************************************/
string Restaurant::get_address() const {
	return address;
}

/*********************************************************************
** Function: get_num_employees
** Description: gets number of employees
** Parameters: na
** Pre-Conditions: text file present
** Post-Conditions: number used later in function
*********************************************************************/
int Restaurant::get_num_employees() {
	int num_employees = 0;
	string line;
	fstream rf;
	rf.open("employee.txt");
	while (getline(rf, line)) { // increments 1 for each line
		num_employees++;
	}
	rf.close();

	return num_employees;
}

/*********************************************************************
** Function: employee_array
** Description: creates array of employees
** Parameters: number of employees
** Pre-Conditions: item declared in class, num of employees initialized
** Post-Conditions: struct is now accesible
*********************************************************************/
employee* Restaurant::employee_array(int num_employees) {

	employee* employees;
	employees = new employee[num_employees]; // creates array on heap

	return employees;
}

/*********************************************************************
** Function: get_employees
** Description: fill employeesz
** Parameters: number of employees
** Pre-Conditions: item declared in class, num of employees initialized
** Post-Conditions: struct is now accesible
*********************************************************************/
void Restaurant::get_employees() {
	fstream rf;
	rf.open("employee.txt");
	int num_employees = get_num_employees();
	employees = employee_array(num_employees);
	for (int i = 0; i < num_employees-1; i++) { //reads employees from file
		rf >> employees[i].id >> employees[i].password >> employees[i].first_name >> employees[i].last_name;
	}

	rf.close();
}

/*********************************************************************
** Function: load_data
** Description: loads data for each part
** Parameters: na
** Pre-Conditions: dta functions declared 
** Post-Conditions: data is now usable
*********************************************************************/
void Restaurant::load_data() {
	fstream f;
	f.open("restaurant_info.txt");
	getline(f, this->name); //gets who line and reads info
	getline(f, this->phone);
	getline(f, this->address);
	
	this->week = new hours[7];
	for (int i = 0; i < 7; i++) {
		f >> week[i].day >> week[i].open_hour >> week[i].close_hour; // reads infor for each item
	}

	f.close();

	get_employees();

}

/*********************************************************************
** Function: get_employee_id
** Description: get employee id input
** Parameters: na
** Pre-Conditions: function called
** Post-Conditions: all int id outputted
*********************************************************************/
string Restaurant::get_employee_id() {
	string s;
	int error = 0;
	do {
		error = 0;
		cout << "Please Enter your ID number: ";
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			if (!(s.at(i) >= '0' && s.at(i) <= '9')) {
				//checks to be sure every letter is an integer
				error = 1;
			}
		}
		if (error == 1)
			cout << "Error! Username must be integers" << endl;
	} while (error == 1);

	return s;
}

/*********************************************************************
** Function: get_employee_password
** Description: gets employee password
** Parameters: na
** Pre-Conditions: function called
** Post-Conditions: password to be matched against system
*********************************************************************/
string Restaurant::get_employee_password() {
	string pass;
	cout << "Please Enter your Password: ";
	cin >> pass;

	return pass;
}

/*********************************************************************
** Function: login
** Description: matches login inputs
** Parameters: id, password
** Pre-Conditions: id and password initialized
** Post-Conditions: login info displayed
*********************************************************************/
int Restaurant::login(string id, string password) {
	int person = -1;

	int x = atoi(id.c_str()); //convert string to integer
	int num_employees = get_num_employees();
	for (int i = 0; i < num_employees - 1; i++) {
		if (((password.compare(employees[i].password) == 0) && (x == employees[i].id))) {
			cout << "Successful Login!" << endl; //if both match for same user success holds person in variable
			person = i;
			break;
		}
		else {
			person = -1;
		}
	}
	if (person == -1) {
		cout << "Error! Try again." << endl;
	}

	return person;
}

/*********************************************************************
** Function: display_login
** Description: displays information on employee
** Parameters: na
** Pre-Conditions: successful login
** Post-Conditions: can now access employee options
*********************************************************************/
void Restaurant::diplay_login() {
	int person = -1;
	do {
		string id = get_employee_id();
		string password = get_employee_password();
		person = login(id, password);
	} while (person == -1); //displays person at pass and id match
	cout << "Welcome " << employees[person].first_name << " " << employees[person].last_name << endl;
}

/*********************************************************************
** Function: view_menu
** Description: displays menu
** Parameters: na
** Pre-Conditions: menu loaded
** Post-Conditions: menu displayed
*********************************************************************/
void Restaurant::view_menu() {
	Menu m1;
	m1.load_menu_data();
	m1.view_pizzas(); // calls functions to display menu
}

/*********************************************************************
** Function: view_hours
** Description: displays hours
** Parameters: na
** Pre-Conditions: data loaded
** Post-Conditions: prints info
*********************************************************************/
void Restaurant::view_hours() {
	load_data();
	for (int i = 0; i < 7; i++) {
		cout << week[i].day << " " << week[i].open_hour << " " << week[i].close_hour << endl;
	}
}

/*********************************************************************
** Function: view_address
** Description: displays address
** Parameters: na
** Pre-Conditions: data loaded
** Post-Conditions: prints info
*********************************************************************/
void Restaurant::view_address() {
	load_data();
	cout << "Address: " << address << endl;
}

/*********************************************************************
** Function: view_phone
** Description: displays phone number
** Parameters: na
** Pre-Conditions: data loaded
** Post-Conditions: prints info
*********************************************************************/
void Restaurant::view_phone() {
	load_data();
	cout << "Phone: " << phone << endl;
}

/*********************************************************************
** Function: get_size
** Description: gets size input
** Parameters: na
** Pre-Conditions: function called
** Post-Conditions: uses size
*********************************************************************/
string Restaurant::get_size() {
	int error = 0;
	string size;
	do {
		cout << "What size(small, medium, large)? ";
		cin >> size; //gets input 
		if (size == "small" || size == "medium" || size == "large") {
			error = 0;
		}
		else {
			cout << "Not valid, try again" << endl;
			error = 1;
		}
	} while (error == 1);

	return size;
}

/*********************************************************************
** Function: search menu by price
** Description: searches menu by price and gives option to add to order
** Parameters: na
** Pre-Conditions: data loaded, function called
** Post-Conditions: adds to order if desired or o back to main screen
*********************************************************************/
void Restaurant::search_menu_by_price() {
	int error = 0;
	int x;
	string s;
	Menu m1;
	do {
		error = 0;
		cout << "Enter your max budget: ";
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			if (!(s.at(i) >= '0' && s.at(i) <= '9')) {
				error = 1;
			}
		}
		if (error == 0) {
			x = atoi(s.c_str());
			if (x <= 0)
				error = 1; //makes sure valid integer input greater than 0
			else {
				string size = get_size(); //calls function
				m1.search_pizza_by_cost(x, size);
			}
		}
	} while (error == 1);
	
}

/*********************************************************************
** Function: search menu by price
** Description: searches menu by price and gives option to add to order
** Parameters: na
** Pre-Conditions: data loaded, function called
** Post-Conditions: adds to order if desired or o back to main screen
*********************************************************************/
void Restaurant::search_by_ingredients() {
	int error = 0;
	string response;
	Pizza p1;
	Menu m1;
	string* ingredients = p1.get_ingredients(); //calls functions
	int num_ingredients = p1.get_num_ingredients();
	do {
		cout << "Do you want to search by ingredients to exclude(E) or include(I): ";
		cin >> response;
		if (response == "E" || response == "I")
			error = 0;
		else
			error = 1; //if not valid try again
	} while (error == 1);
	if(response == "I")
		m1.search_pizza_by_ingredients_to_include(ingredients, num_ingredients); //calls according functions
	else
		m1.search_pizza_by_ingredients_to_exclude(ingredients, num_ingredients);
}

/*********************************************************************
** Function: change hours
** Description: changes hours in file
** Parameters: na
** Pre-Conditions: function called
** Post-Conditions: updates text file
*********************************************************************/
void Restaurant::change_hours() {
	string day, open, close;
	int count = 0;
	string line;
	fstream rf;
	rf.open("restaurant_info.txt");
	do {
		cout << "Which day would you like to change the hours for: ";
		cin >> day;
		cout << "What will the opening time be: ";
		cin >> open;
		cout << "What will the closing time be: ";
		cin >> close;
		for (int i = 0; i < 7; i++) {
			if (week[i].day == day) {
				week[i].open_hour = open;
				week[i].close_hour = close;
				count++;
			}
		}
		if (count == 0)
			cout << "ERROR, try again" << endl;
	} while (count == 0);
	ofstream temp;
	temp.open("temp.txt");  //puts into temporary file
	temp << "Bytes Pizzas" << endl;
	temp << phone << endl;
	temp << address << endl;
	for (int i = 0; i < 7; i++) {
		temp << week[i].day << " " << week[i].close_hour << " " << week[i].close_hour << endl;
	}
	temp.close();
	rf.close();
	remove("restaurant_info.txt"); //deletes previous file
	rename("temp.txt", "restaurant_info.txt"); // renames temp file
}

/*********************************************************************
** Function: view order
** Description: displays orders
** Parameters: na
** Pre-Conditions: function called
** Post-Conditions: prints orders
*********************************************************************/
void Restaurant::view_orders() {
	fstream wf;
	string cust_name;
	wf.open("orders.txt");
	Menu m1;
	string order_num, amount, line;
	string name, card, phone, pizza, size;
	int num_orders = m1.get_num_orders();

	for (int i = 0; i < num_orders; i++) {
		getline(wf, line); //gets entire order line
		cout <<" (" << i << ") "<< line << endl;
	}

	wf.close();
}

/*********************************************************************
** Function: remove order
** Description: removes order from text file
** Parameters: na
** Pre-Conditions: text file present, function called
** Post-Conditions: removes desired order and updates file
*********************************************************************/
void Restaurant::remove_orders() {
	Menu m1;
	view_orders();

	cout << "Which would you like to remove?" << endl;
	int x = m1.get_integer();

	string line;
	int count = 0;

	fstream rf;
	rf.open("orders.txt");
	ofstream temp;
	temp.open("temp.txt");
	while (getline(rf, line)) {
		++count;
		if (count != x) {
			temp << line << endl; //adds back to file if not removed
		}
	}
	cout << "Order Removed" << endl;
	temp.close();
	rf.close();
	remove("orders.txt"); //removes previous file
	rename("temp.txt", "orders.txt"); //renames temporary file
}
