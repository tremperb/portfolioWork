/******************************************************
** Program: zoo.h
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: Defines zoo class
******************************************************/

#ifndef ZOO_H
#define ZOO_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include "animal.h"
#include "monkey.h"
#include "meerkat.h"
#include "otter.h"

class Zoo {
private:
	int total_monkeys;
	int total_meerkats;
	int total_otters;
	float balance;
	float foodCost;
	Animal ** animals;
	int count;
public:
	Zoo();
	~Zoo();
	void set_total_monkeys(const int &total_monkeys);
	int get_total_monkeys() const;
	void set_total_meerkats(const int &total_meerkats);
	int get_total_meerkats() const;
	void set_total_otters(const int &total_otters);
	int get_total_otters() const;
	void set_balance(const float& balance);
	float get_balance() const;
	void set_foodCost(const float& foodCost);
	float get_foodCost() const;
	void play_game();
	void intro();
	void special_event();
	void create_animal();
	void get_animal();
	int get_num(string &type);
	void check_balance();
	void get_sick();
	int get_roll();
	int check_roll(int &roll);
	void fix_sick_animal(int &roll, int &nextRoll);
	void remove_animal(int &roll, int &nextRoll);
	void remove_monkey(int &roll, int &nextRoll);
	void remove_meerkat(int &roll, int &nextRoll);
	void remove_otter(int &roll, int &nextRoll);
	void get_baby();
	void add_monkey(int &roll, int &nextRoll);
	void add_meerkat(int &roll, int &nextRoll);
	void add_otter(int &roll, int &nextRoll);
	void get_revenue();
	void random_bonus();
	int sick_roll();
	int check_sick_roll(int &roll);
	void get_food_amount();
	void increment_age();
	void display_animals();
	void new_food_cost();
	void add_adult_monkey(int &num);
	void add_adult_otter(int &num);
	void add_adult_meerkat(int &num);
};
#endif


