/*********************************************************************
** Program Filename: escape.h
** Description: header file
*********************************************************************/

#ifndef ESCAPE_H
#define ESCAPE_H
#include "event.h"
class Escape : public Event {
public:
	Escape();
	~Escape();
	int encounter();
	void percept();

};
#endif