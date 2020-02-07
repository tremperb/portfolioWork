/******************************************************
 * ** Program: driver.cpp (Linked List)
 * ** Author: Brayden Tremper
 * ** Date: 06/06/2019
 * ** Description: This program makes a linked list class.
 * **					 it utilizes only pointers (no array, etc)
 * **              It then tests this in a small game.
 * **					 (read text file for more info)
 * ** Input: Takes in the numbers, whether to add more and type of sorting
 * ** Output: Outputs the printed list, how any primes, and the clears the list.
 * ******************************************************/



#include <iostream>
#include <string>
#include "linked_list.h"

using namespace std;

/*********************************************************************
** Function: main
** Description: calls play game
*********************************************************************/
int main() {
	Linked_List list;
	list.play_game();

//	system("pause");
	return 0;
}
