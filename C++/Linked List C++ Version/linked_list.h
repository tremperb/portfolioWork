#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linked_list_node.h"
#include <iostream>
#include <string>

using namespace std;
class Linked_List {
private:
	unsigned int length; // the number of nodes contained in the list
	Linked_List_Node *first; // a pointer to the first node in the list
	Linked_List_Node *new_node;
	
public:
	Linked_List();
	int get_length();
	void print(); 
	void clear(); // delete the entire list (remove all nodes and reset length to 0)




	unsigned int push_front(int new_data); // insert a new value at the front of the list (returns the new length of the list)

	unsigned int push_back(int new_data); // insert a new value at the back of the list (returns the new length of the list)

	unsigned int insert(int val, unsigned int index); // insert a new value in the list at the specified index (returns the new length of the list)
	void sort_ascending(); // sort the nodes in ascending order. You must implement the recursive Merge Sort algorithm
	// Note: it's okay if sort_ascending() calls a recursive private function to perform the sorting.
	void sort_descending(); // sort the nodes in descending order
	int get_primes();
	// you can add extra member variables or functions as desired
	void merge_sort(Linked_List_Node** headRef, char &direction);
	Linked_List_Node* merge(Linked_List_Node* a, Linked_List_Node* b, char &direction);
	void split(Linked_List_Node* source, Linked_List_Node** frontRef, Linked_List_Node** backRef);
	/*-------------------------------------------------*/
	int get_integer();
	void play_game();
};
#endif
