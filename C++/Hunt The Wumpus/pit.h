/*********************************************************************
** Program Filename: pit.h
** Description: header file
*********************************************************************/

#ifndef PIT_H
#define PIT_H
#include "event.h"
class Pit : public Event {
public:
	Pit();
	~Pit();
	int encounter();
	void percept();
	
};
#endif
