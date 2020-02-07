/*here*/

#ifndef PIZZA
#define PIZZA
#include <iostream>
#include <string>

using namespace std;

class Pizza{
	private:
		string name;
		int small_cost;
		int medium_cost;
		int large_cost;
		int num_ingredients;
		string* ingredients;

	public:
		Pizza();
		~Pizza();
		Pizza(const Pizza& pie);
		Pizza & operator=(const Pizza & pie);

		void set_name(const string &name);
		void set_num_ingredients(const int &num);
		void set_small_cost(const int &cost);
		void set_medium_cost(const int &cost);
		void set_large_cost(const int &cost);

		string get_name()const;
		int get_num_ingredients()const;
		string* get_ingredients()const;
		int get_small_cost()const;
		int get_medium_cost()const;
		int get_large_cost()const;

		void set_ingredients_array(const int &num);
		void fill_ingredients_array(const int num, string temp[]);
};
#endif
