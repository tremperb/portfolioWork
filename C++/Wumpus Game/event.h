/*********************************************************************
** Program Filename: event.h
** Description: header file
*********************************************************************/
#ifndef EVENT_H
#define EVENT_H
#include "room.h"
#include <iostream>

using namespace std;

class Event {
	public:
		virtual int encounter() = 0;	//abstract functions only
		virtual void percept() = 0;
};
#endif

