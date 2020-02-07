/*********************************************************************
** Program Filename: gold.h
** Description: header file
*********************************************************************/

#ifndef GOLD_H
#define GOLD_H
#include "event.h"

class Gold : public Event {	
public:
	Gold();
	~Gold();
	int encounter();
	void percept();
	
};
#endif

