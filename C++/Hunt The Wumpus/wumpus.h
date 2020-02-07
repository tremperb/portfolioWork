/*********************************************************************
** Program Filename: wumpus.h
** Description: header file
*********************************************************************/

#ifndef WUMPUS_H
#define WUMPUS_H
#include "event.h"
class Wumpus : public Event {
public:
	int encounter();
	void percept();
};
#endif
