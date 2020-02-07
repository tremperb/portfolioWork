#pragma once
#include <iostream>
/******************************************************
** Program: animal.h
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: Defines animal class
******************************************************/
#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>

using namespace std;

class Animal {
protected:
	int age;
	int price;
	int num_babies;
	int food_cost;
	int revenue;

public:
	Animal();
	Animal(int age, int price, int num_babies, int food_cost, int revenue);
	Animal(const Animal & Copy);
	Animal & operator=(const Animal & Copy);
	~Animal();
	int get_age() const;
	int get_price() const;
	int get_num_babies() const;
	int get_food_cost() const;
	int get_revenue() const;
};
#endif
