/******************************************************
** Program: driver.cpp (Zoo Tycoon)
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: Calls game and runs
** Input: Various inputs from user to create their zoo
** Output: Outputs responses and the list of animals w/ age
******************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include "zoo.h"

using namespace std;

int main() {
	Zoo z;
	z.play_game();
//	system("pause"); //take out when switching to vim
	return 0;
}
