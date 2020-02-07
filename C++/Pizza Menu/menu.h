/*menu class*/

#ifndef MENU
#define MENU
#include <iostream>
#include <string>
#include <vector>
#include "pizza.h"

using namespace std;

class Menu{
	private:
		int num_pizzas;
		Pizza* pizzas;
	public:
		Menu();
		~Menu();
		Menu(const Menu &);
		Menu & operator=(const Menu &);


		void set_num_pizzas(const int num_pizzas);
		int get_num_pizzas()const;
		int get_lines();
	
		void load_menu_data();
		void load_ingredients(fstream &rf, int num_in, int current_pizza);
		void view_pizzas();
		
		void search_pizza_by_cost(int upper_bound, string size);
		void make_selection(string size, int count);
		void check_selection(int &selection, int selection_array[10], int amount_array[10], int &count, int &num_items, string &size);
		int get_num_orders();
		int get_new_num();
		void get_customer(int selection_array[10], int amount_array[10], int &num_iems,  string &size);
		void add_to_order(string &cust_name, string &phone, string &card, int &order_num, string &size, int selection_array[], int amount_array[], int &num_items);
		void search_pizza_by_ingredients_to_include(string* ingredients, int num_ingredients);
		void search_pizza_by_ingredients_to_exclude(string* ingredients, int num_ingredients);
		string get_size();
		int get_integer();
		void place_order();
		void get_add_to_menu();
		void add_to_menu(string &name, int &smallCost, int &mediumCost, int &largeCost, int &numIngredients, vector <string>ingred_array);
		void get_pizza_remove();
		void remove_from_menu(int index_of_pizza_on_menu);
};
#endif
