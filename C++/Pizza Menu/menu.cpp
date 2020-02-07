#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "menu.h"
#include "pizza.h"
#include "Header.h"

using namespace std;
/*********************************************************************
** Function: menu
** Description: initializes standard values
*********************************************************************/
Menu::Menu() {
	num_pizzas = 0;
	pizzas = NULL;
}

/*********************************************************************
** Function: ~menu
** Description: deletes memory at end of program
*********************************************************************/
Menu::~Menu() {
	if (pizzas != NULL) {
		delete[] pizzas; //deletes allocated memory
	}
}

/*********************************************************************
** Function: menu
** Description: creates menu copy
*********************************************************************/
Menu::Menu(const Menu& copy) {
	this->num_pizzas = copy.num_pizzas;
	if (this->num_pizzas > 0) {
		this->pizzas = new Pizza[this->num_pizzas];
		for (int i = 0; i < this->num_pizzas; i++) {
			this->pizzas[i] = copy.pizzas[i]; //coppies info
		}
	}
	else
		this->pizzas = NULL;
}

/*********************************************************************
** Function: menu operator
** Description: creates menu operator allowing item to be coppied
*********************************************************************/
Menu& Menu::operator=(const Menu& copy) {
	int num_pizzas = get_lines();
	this->num_pizzas = copy.num_pizzas;
	if (num_pizzas > 0) {
		pizzas = new Pizza[num_pizzas];
		for (int i = 0; i < num_pizzas; i++) {
			pizzas[i] = copy.pizzas[i];
		}
	}
	else {
		this->pizzas = NULL;
	}
	return *this;
}

/*********************************************************************
** Function: set num pizzas
** Description: allows access to private variable
*********************************************************************/
void Menu::set_num_pizzas(const int num_pizzas) {
	this->num_pizzas = num_pizzas;
}

/*********************************************************************
** Function: get num pizzas
** Description: gets access to private variable
*********************************************************************/
int Menu::get_num_pizzas() const{
	return num_pizzas;
}

/*********************************************************************
** Function: get lines
** Description: get number of lines aka num of pizzas
*********************************************************************/
int Menu::get_lines() {
	int num_pizzas = 0;
	string line;
	fstream rf;
	rf.open("menu.txt");
	while (getline(rf, line)) {
		num_pizzas++; //after linens inrement
	}
	rf.close();

	return num_pizzas;
}

/*********************************************************************
** Function: load menu data
** Description: loads data from emnu file
*********************************************************************/
void Menu::load_menu_data() {
	fstream rf;
	rf.open("menu.txt");
	string dummyLine, name;
	int small_cost, medium_cost, large_cost, num_ingredients;
	int num_pizzas = get_lines();
	pizzas = new Pizza[num_pizzas];

	for (int i = 0; i < num_pizzas; i++) {
		//reas in info and assigns
		rf >> name >> small_cost >> medium_cost >> large_cost >> num_ingredients;
		pizzas[i].set_name(name);
		pizzas[i].set_small_cost(small_cost);
		pizzas[i].set_medium_cost(medium_cost);
		pizzas[i].set_large_cost(large_cost);
		pizzas[i].set_num_ingredients(num_ingredients);
		pizzas[i].set_ingredients_array(num_ingredients);
		load_ingredients(rf, num_ingredients, i);

	}
	rf.close();
}

/*********************************************************************
** Function: view pizzas
** Description:  printss menu with all aspects
*********************************************************************/
void Menu::view_pizzas() {
	load_menu_data();
	int num_pizzas = get_lines();
	
	for (int i = 0; i < num_pizzas -1; i++) {
		cout << i << ". "<< pizzas[i].get_name() << " " << pizzas[i].get_small_cost() << " ";
		cout << pizzas[i].get_medium_cost() << " " << pizzas[i].get_large_cost() << " ";
		cout << pizzas[i].get_num_ingredients() << " ";
		string *temp = pizzas[i].get_ingredients(); //stores ingredients in temp array
		for (int j = 0; j < pizzas[i].get_num_ingredients(); j++) {
			cout << temp[j] << " ";
		}
		cout << endl;
	}
}

/*********************************************************************
** Function: load ingredients
** Description:  printss menu with all aspects
*********************************************************************/
void Menu::load_ingredients(fstream &rf, int num_in, int current_pizza) {
	string* temp = new string[num_in];
	
	for (int i = 0; i < num_in; i++) {
       rf >> temp[i]; //reads to get new array of current ingredients
	}

   pizzas[current_pizza].fill_ingredients_array(num_in, temp);
   delete [] temp;
}

/*********************************************************************
** Function: search pizza by cost
** Description:  searches for pizza by user inputted cost
*********************************************************************/
void Menu::search_pizza_by_cost(int upper_bound, string size) {
	load_menu_data();
	int smalls = 1, mediums = 1, larges = 1, count =0;
	int num_pizzas = get_lines();

	if (size == "small") {
		for (int i = 0; i < num_pizzas -1; i++) {
			if (pizzas[i].get_small_cost() <= upper_bound) { // if less than max, same for each size
				cout << i << ". Small " << pizzas[i].get_name() << " - " << pizzas[i].get_small_cost() << endl;
				count++;
			}
			else
				smalls = 0;
		}
	}
	if (size == "medium") {
		for (int i = 0; i < num_pizzas -1; i++) {
			if (pizzas[i].get_medium_cost() <= upper_bound) {
				cout << i << ". Medium " << pizzas[i].get_name() << " - " << pizzas[i].get_medium_cost() << endl;
				count++;
			}
			else 
				mediums = 0;
		}
	}
	if (size == "large") {
		for (int i = 0; i < num_pizzas - 1; i++) {
			if (pizzas[i].get_large_cost() <= upper_bound) {
				cout << i << ". Large " << pizzas[i].get_name() << " - " << pizzas[i].get_large_cost() << endl;
				count++;
			}
			else
				larges = 0;
		}
	}
	if (smalls == 0 || mediums == 0 || larges == 0)
		cout << "No results" << endl;
	else
		make_selection(size, count); //if match allow option to make orderr
}

/*********************************************************************
** Function: make selction
** Description: option to make order for desired pizzas
*********************************************************************/
void Menu::make_selection(string size, int count) {
	string response;
	int error = 0, selection, amount, num_items=0;
	int selection_array[10], amount_array[10], k = 0, j = 0;
	
	cout << "Would you like to place an order off of these results?(Yes/No)";
	cin >> response;
	if (response == "yes" || response == "Yes") {
		do {
			cout << "Please make a selection or enter '-1' to cancel or enter '-2' to proceed to checkout: ";
			cin >> selection;
			if (size == "small") {
				if (selection == -1 || selection == -2)
					break;
				cout << "How many small " << pizzas[selection].get_name() << "? ";
				amount = get_integer();
				num_items++;
				selection_array[k++] = selection; //stores selection in array
				amount_array[j++] = amount; //stores amount for corresponding section
			}
			if (size == "medium") {
				if (selection == -1 || selection == -2)
					break;
				cout << "How many medium " << pizzas[selection].get_name() << "? ";
				amount = get_integer();
				num_items++;
				selection_array[k++] = selection;
				amount_array[j++] = amount;
			}
			if (size == "large") {
				if (selection == -1 || selection == -2)
					break;
				cout << "How many large " << pizzas[selection].get_name() << "? ";
				amount = get_integer();
				num_items++;
				selection_array[k++] = selection;
				amount_array[j++] = amount;
			}
		} while (selection >= 0);
		check_selection(selection, selection_array, amount_array, count, num_items, size);
	}
}

/*********************************************************************
** Function: check slection
** Description: checks how to respond to user selection
*********************************************************************/
void Menu::check_selection(int &selection, int selection_array[10], int amount_array[10], int &count, int &num_items, string &size) {
	if(selection == -1) {
		cout << "Order Canceled" << endl;
	}
	else if (selection == -2) {
		cout << "Initiate Checkout" << endl;
		get_customer(selection_array, amount_array, num_items, size);
	}
}

/*********************************************************************
** Function: get num orders
** Description:  gets current number of orders
*********************************************************************/
int Menu::get_num_orders() {
	int num_orders = 0;
	string line;
	fstream rf;
	rf.open("orders.txt");
	while (getline(rf, line)) {
		num_orders++; //increments orders for each line
	}
	rf.close();

	return num_orders;
}

/*********************************************************************
** Function: get_new_num
** Description:  gets number of order to be used when adding to text 
file and order number for each order
*********************************************************************/
int Menu::get_new_num() {
	fstream rf;
	int order_num;
	rf.open("orders.txt");
	rf >> order_num; //stores order number
	rf.close();

	return order_num;
}

/*********************************************************************
** Function: get customer
** Description: gets customer info
*********************************************************************/
void Menu::get_customer(int selection_array[10], int amount_array[10], int &num_items, string &size) {
	string cust_name, phone, card;
	int order_num = 0;
	cout << "Please Provide the following information" << endl;
	cout << "Customer name: ";
	cin.ignore(); //ignores so you can see all string inputs, empty register
	getline(cin, cust_name);
	cout << "Credit card number: ";
	getline(cin, card);
	cout << "Phone Number: ";
	getline(cin, phone);
	order_num = get_new_num();
	add_to_order(cust_name, phone, card, order_num, size, selection_array, amount_array, num_items);
	cout << "Thank you, " << cust_name << " your order number is " << ++order_num << endl;
}

/*********************************************************************
** Function: get size
** Description:  gets pizza size
*********************************************************************/
string Menu::get_size() {
	int error = 0;
	string size;
	do {
		cout << "What size(small, medium, large)? ";
		cin >> size;
		if (size == "small" || size == "medium" || size == "large") {
			error = 0;
		}
		else {
			cout << "Not valid, try again" << endl;
			error = 1;
		}
	} while (error == 1); //do while not valid input

	return size;
}

/*********************************************************************
** Function: search pizza by ingredients to include
** Description: searches for ingredients to include 
*********************************************************************/
void Menu::search_pizza_by_ingredients_to_include(string* ingredients, int num_ingredients) {
	string include_array[10];
	string more = "yes";
	int count = 0;
	string size = get_size();
	for (int i = 0; i < 10; i++) {
		count++;
		cout << "What item would you like to include: ";
		cin >> include_array[i];						//stores in array
		cout << "Would you like to include another ingredient(yes/no)? ";
		cin >> more;
		if (more == "no" || more == "No")
			break;
	}
	int num_pizzas = get_lines();
	int blah = 0;
	load_menu_data();
	cout << "Here are the pizzas that match your criteria:" << endl;
	int matches_array[20], match=0, total_match=0; 
	int pizzas_match[20], m = 0;
		for (int i = 0; i < num_pizzas - 1; i++) {
			match = 0;
			total_match = 0;
			string *temp = pizzas[i].get_ingredients();
			for (int j = 0; j < pizzas[i].get_num_ingredients(); j++) {
				for (int k = 0; k < count; k++) {
					if (include_array[k].compare(temp[j]) == 0) { // checks if match
						match = 1;
						total_match = match + total_match;
						matches_array[i] = total_match;
						if (matches_array[i] == count) { //checks to make sure both match
							blah++;
							pizzas_match[m++] = i;
							cout << i << ". " << pizzas[i].get_name() << " " << pizzas[i].get_small_cost() << " ";
							cout << pizzas[i].get_medium_cost() << " " << pizzas[i].get_large_cost() << " ";
							cout << pizzas[i].get_num_ingredients() << " ";
							for (int j = 0; j < pizzas[i].get_num_ingredients(); j++) {
								cout << temp[j] << " ";
							}
							cout << endl;
						}
					}
				//delete[] temp;	
				}
			}
		}
		make_selection(size, count);
}

/*********************************************************************
** Function: search pizza by ingredients to exclude
** Description: searches for ingredients to exclude
*********************************************************************/
void Menu::search_pizza_by_ingredients_to_exclude(string* ingredients, int num_ingredients) {
	string exclude_array[10];
	string more = "yes";
	int count = 0;
	string size = get_size();
	for (int i = 0; i < 10; i++) {
		count++;
		cout << "What item would you like to exclude: ";
		cin >> exclude_array[i];						//stores desird options in array
		cout << "Would you like to include another ingredient(yes/no)? ";
		cin >> more;
		if (more == "no" || more == "No")
			break;
	}
	int num_pizzas = get_lines();
	load_menu_data();
	cout << "Here are the pizzas that match your criteria:" << endl;
	int matches_array[20], match = 0, total_match = 0;
	int pizzas_match[20], m = 0;
	for (int i = 0; i < num_pizzas - 1; i++) {
		match = 0;
		total_match = 0;
		string *temp = pizzas[i].get_ingredients();
		for (int j = 0; j < pizzas[i].get_num_ingredients(); j++) {
			for (int k = 0; k < count; k++) {
				if (exclude_array[k].compare(temp[j]) == 0) {
					pizzas[i].set_name("NO");		//if not excluded change name to no
				}

			}
		}
		if (pizzas[i].get_name() != "NO") { //if the name is equal to NO dont do that one
			match = 1;
			total_match = match + total_match;
			matches_array[i] = total_match;
			pizzas_match[m++] = i;
			cout << i << ". " << pizzas[i].get_name() << " " << pizzas[i].get_small_cost() << " ";
			cout << pizzas[i].get_medium_cost() << " " << pizzas[i].get_large_cost() << " ";
			cout << pizzas[i].get_num_ingredients() << " ";
			for (int j = 0; j < pizzas[i].get_num_ingredients(); j++) {
				cout << temp[j] << " ";
			}
			cout << endl;
		}
	}
	make_selection(size, count); // make selection on order
}

/*********************************************************************
** Function: place order
** Description: display info for user to place order
*********************************************************************/
void Menu::place_order() {
	int count = 0;

	view_pizzas();
	string size = get_size();
	
	make_selection(size, count);
}

/*********************************************************************
** Function: adds to order
** Description: adds the desired item to order and updates text file
*********************************************************************/
void Menu::add_to_order(string &cust_name, string &phone, string &card, int &order_num, string &size, int selection_array[], int amount_array[], int &num_items) {
	int selection, amount;
	ofstream wf;
	wf.open("orders.txt", std::ios::app);
	wf << ++order_num << " " << cust_name << " " << card << " " << phone << " ";

	for (int i = 0; i < num_items; i++) {
		selection = selection_array[i];
		amount = amount_array[i];
		wf << pizzas[selection].get_name() << " " << size  << " " << amount << " ";
	}
	wf << endl;
	wf.close();
}

/*********************************************************************
** Function: get integer
** Description: error checking function for integer inuts
*********************************************************************/
int Menu::get_integer() {
	int error = 0;
	float x;
	string s;
	do {
		error = 0;
		cout << "Enter your input: ";
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			if (!(s.at(i) >= '0' && s.at(i) <= '9')) {
				cout << "ERROR!" << endl;
				error = 1;
			}
			if (error == 0) {
				x = atoi(s.c_str());
				if (x <= 0) {
					error = 1;
					cout << "ERROR" << endl;
				}
			}
		}
	} while (error == 1);

	return x;
}

/*********************************************************************
** Function: get_add_to_menu
** Description: get information of new pizza to add to menu
*********************************************************************/
void Menu::get_add_to_menu() {
	string name, ingredient;
	int smallCost, mediumCost, largeCost, numIngredients;
	cout << "Please Provide the following information" << endl;
	cout << "Please enter the pizza name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Please enter the small cost" << endl;
	smallCost = get_integer();
	cout << "Please enter the medium cost" << endl;
	mediumCost = get_integer();
	cout << "Please enter the large cost" << endl;;
	largeCost = get_integer();
	cout << "Please enter the number of ingredients" << endl;
	numIngredients = get_integer();
	vector <string>ingred_array; //using vector instead of array 
	cin.ignore();
	for (int i = 0; i < numIngredients; i++) {
		cout << "Please enter an ingredient: ";
		getline(cin, ingredient);//gets ingredient
		ingred_array.push_back(ingredient); //stores in vector
	}
	add_to_menu(name, smallCost, mediumCost, largeCost, numIngredients, ingred_array);
}

void Menu::add_to_menu(string &name, int &smallCost, int &mediumCost, int &largeCost, int &numIngredients, vector <string>ingred_array) {
	ofstream wf;
	wf.open("menu.txt", std::ios::app);
	wf << name << " " << smallCost << " " << mediumCost << " " << largeCost << " " << numIngredients << " ";

	for (int i = 0; i < numIngredients; i++) {
		wf << ingred_array[i] << " "; // writes all ingredients to file
	}
	wf << endl;
	wf.close();
}

/*********************************************************************
** Function: get pizza to remove
** Description: gets user desired pizza to remove fromm menu
*********************************************************************/
void Menu::get_pizza_remove() {
	int error = 0;
	float x;
	string s;
	int num_pizzas = get_lines();
	view_pizzas();
	do {
		error = 0;
		cout << "Select the option for the pizza to remove: ";
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			if (!(s.at(i) >= '0' && s.at(i) <= '9')) {
				cout << "ERROR!" << endl;
				error = 1;
			}
			if (error == 0) {
				x = atoi(s.c_str());
				if (x > num_pizzas) {
					cout << "ERROR!" << endl;
					error = 1;
				}
			}
		}
	} while (error == 1);
	x++;
	remove_from_menu(x); //gets input and then made for use in function 

}

/*********************************************************************
** Function: remove from menu
** Description: removes pizza from menu
*********************************************************************/
void Menu::remove_from_menu(int index_of_pizza_on_menu) {
	string line;
	int count = 0;
	
	fstream rf;
	rf.open("menu.txt");
	ofstream temp;
	temp.open("temp.txt");
	while (getline(rf, line)) {
		++count;
		if (count != index_of_pizza_on_menu) {
			temp << line << endl; // stores in temporary text file if not being removedd
		}
	}
	cout << pizzas[--index_of_pizza_on_menu].get_name() << " has been removed" << endl;
	temp.close();
	rf.close();
	remove("menu.txt"); //deletes file
	rename("temp.txt", "menu.txt"); // renames temporary file to that which was deleted
}
