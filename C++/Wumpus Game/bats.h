/*********************************************************************
** Program Filename: bats.h
** Description: header file
*********************************************************************/

#ifndef BATS_H
#define BAT_H
#include "event.h"
class Bats : public Event {
public:
	Bats();
	~Bats();
	int encounter();
	void percept();
};
#endif

