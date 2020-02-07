/******************************************************
** Program: otter.h
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: defines otter class
******************************************************/
#ifndef OTTER_H
#define OTTER_H

#include <iostream>
#include "animal.h"

class Otter : public Animal {	//inheriting from animal
public:
	Otter();
	Otter(int age);
	~Otter();
	Otter(const Otter& Copy);
	Otter & operator=(const Otter &Copy);
};
#endif

