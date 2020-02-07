/******************************************************
** Program: monkey.h
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: defines monkey class
******************************************************/

#ifndef MONKEY_H
#define MONKEY_H

#include <iostream>
#include "animal.h"
class Monkey : public Animal {	//inherits from animal
private:
	
public:
	Monkey();
	Monkey(int age);
	~Monkey();
	Monkey(const Monkey& Copy);
	Monkey & operator=(const Monkey &Copy);

};
#endif

