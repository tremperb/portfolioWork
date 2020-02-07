/******************************************************
** Program: meerkat.h
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: defines meerkat class
******************************************************/
#ifndef MEERKAT_H
#define MEERKAT_H

#include <iostream>
#include "animal.h"

class Meerkat : public Animal {		//inherits from animal
public:
	Meerkat();
	Meerkat(int age);
	~Meerkat();
	Meerkat(const Meerkat& Copy);
	Meerkat & operator=(const Meerkat &Copy);
};
#endif

