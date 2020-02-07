#include "linked_list.h"

/*********************************************************************
 ** Function: Linked_List
 ** Description: default constructor
 *********************************************************************/
Linked_List::Linked_List() {
	length = 0;
	first = nullptr;
}

/*********************************************************************
 ** Function: get length
 ** Description: get our length for list
 *********************************************************************/
int Linked_List::get_length() {
	return length;
}

/*********************************************************************
 ** Function: print
 ** Description: prints all values in linked list
 *********************************************************************/
void Linked_List::print() {

	Linked_List_Node *temp;  //create temp so it doesn't affect our nodes
	temp = first;
	cout << "Your List: ";
	for (unsigned int i = 1; i <= length; i++) {
		if (length == i)
			cout << temp->val;		//display our value	
		else
			cout << temp->val << ", ";
		temp = temp->next;				//get next node
		if (i == 10)
			cout << endl;
	}

	cout << endl;
}

/*********************************************************************
 ** Function: clear
 ** Description: deletes all nodes and resets length to 0 & makes first 
 **				point to "nullptr"
 *********************************************************************/
void Linked_List::clear() {
	Linked_List_Node *temp = first;

	while (temp != nullptr) {
		new_node = temp->next;
		delete temp;
		temp = new_node;
	}

	first = nullptr;	//set first to null ptr
	length = 0;			//reset length
}

/*********************************************************************
 ** Function: push back
 ** Description: inserts a new value at the front of list and returns new length
 *********************************************************************/
unsigned int Linked_List::push_back(int new_data) {

	if (length == 0) {  // Check if list is empty
		new_node = new Linked_List_Node;
		first = new_node;
	}
	else {
		while (new_node->next != nullptr) {
			new_node = new_node->next;			//get our new null until this next does not point to empty
		}
		new_node->next = new Linked_List_Node;
		new_node = new_node->next;
	}
	new_node->val = new_data;	//set the given value to our value for that node
	new_node->next = nullptr;	//point next value to nullptr

	length++;

	return length;
}

/*********************************************************************
 ** Function: push front
 ** Description: inserts a new value at the back of list and returns new length
 *********************************************************************/
unsigned int Linked_List::push_front(int new_data) {
	new_node = new Linked_List_Node;
	if (length == 0) {
		first = new_node;
		new_node->val = new_data;	//set the given value to our value for that node
		new_node->next = nullptr;	//point next value to nullptr
	}
	else {
		new_node->val = new_data;
		new_node->next = first;
		first = new_node;
	}
	length++;
	return length;
}; 

/*********************************************************************
 ** Function: insert
 ** Description: inserts int at user specified index
 *********************************************************************/
unsigned int Linked_List::insert(int val, unsigned int index) {
	if (index == 1) {
		push_back(val);
	}
	else if (index == length + 1) {
		push_front(val);
	}
	else if (index > 1 && index <= length) {
		length++;
		cout << "good" << endl;
		new_node = first;
		for (unsigned int i = 1; i < index - 1; i++) {
			new_node = new_node->next;
		}
		Linked_List_Node *temp = new Linked_List_Node;	//create temp node
		temp = new_node->next;							//store the next node in temp 
		new_node->next = new Linked_List_Node;
		new_node = new_node->next;						//insert new node
		new_node->val = val;							//insert value
		new_node->next = temp;							//make that new node point to the node(s) after index
	}
	else {
		cout << "ERROR: This is not within your lists bounds" << endl;
	}
	return length;
}

/*********************************************************************
 ** Function: sort ascending
 ** Description: sorts our linked list in ascending order and calls
 **				merge sort in regards to it
 *********************************************************************/
void Linked_List::sort_ascending() {
	if (length == 1)
		cout << "You only have one element" << endl;
	else if (length == 0)
		cout << "Your list is currently empty" << endl;
	else {
		char d = 'a';
		merge_sort(&first, d);
	}
}

/*********************************************************************
 ** Function: sort descending
 ** Description: sorts our linked list in descending order and calls 
 **				merge sort in regards to it 
 *********************************************************************/
void Linked_List::sort_descending() {
	if (length == 1)
		cout << "You only have one element" << endl;//no need to sort
	else if (length == 0)
		cout << "Your list is currently empty" << endl;
	else {
		char d = 'd';
		merge_sort(&first, d);
	}
}

/*********************************************************************
 ** Function: merge
 ** Description: Uses merge sort algorithm to split our list and sort
 *********************************************************************/
void Linked_List::merge_sort(Linked_List_Node** firstRef, char &direction) {
	Linked_List_Node* front = *firstRef;
	Linked_List_Node  *a, *b;

	if ((front == nullptr) || (front->next == nullptr)) {	//base case for recursion, if its reached all elements it can now return
		return;
	}

	split(front, &a, &b);			//split our list into halves
	merge_sort(&a, direction);			//sort each side
	merge_sort(&b, direction);

	*firstRef = merge(a, b, direction);	//put the sorted sides together
}

/*********************************************************************
 ** Function: merge
 ** Description: sort and merge our lists
 *********************************************************************/
Linked_List_Node* Linked_List::merge(Linked_List_Node* a, Linked_List_Node* b, char &direction) {
	Linked_List_Node* result;	//result to store our node

	if (a == nullptr)	//base case return the half which is not at the end
		return b;
	else if (b == nullptr)
		return a;

	if (direction == 'a') {		//if this is a sort ascending
		if (a->val < b->val) {	//check if a is less than b
			result = a;	
			result->next = merge(a->next, b, direction);	//now do it again based on the next element
		}
		else {	//otherwise do it in regards to b 
			result = b;
			result->next = merge(a, b->next, direction);	//keep going until basecase is satisfied
		}
	}
	else {	//otherwise it is d so descending
		if (a->val > b->val) {	//check if a is greater than b
			result = a;
			result->next = merge(a->next, b, direction);
		}
		else {
			result = b;
			result->next = merge(a, b->next, direction);
		}
	}

	return result;	//return our result
}

/*********************************************************************
 ** Function: split
 ** Description: splits our list in half each stored in a or b
 *********************************************************************/
void Linked_List::split(Linked_List_Node* source, Linked_List_Node** a, Linked_List_Node** b) {
	Linked_List_Node* split_1;	
	Linked_List_Node* split_2;	
	split_2 = source;
	split_1 = source->next;

	for(unsigned int i=0; i < length; i++) {
		if (split_1 == nullptr)	//if at end break
			break;
		split_1 = split_1->next;	//store the next element 
		if (split_1 != nullptr) {	//if the next element isn't at end
			split_2 = split_2->next;	//get next for that side
			split_1 = split_1->next;	//store next for that
		}
	}

	*a = source;	//store in a side(left)
	*b = split_2->next;	//store in b
	split_2->next = nullptr;	//set next to null
}

/*********************************************************************
 ** Function: get primes
 ** Description: gets primes by checking if remainder
 *********************************************************************/
int Linked_List::get_primes() {
	Linked_List_Node *temp;		//create temp so it doesn't affect our nodes
	temp = first;
	int tempValue;
	int count = 0;

	for (unsigned int i = 1; i <= length; i++) {
		tempValue = temp->val;
		bool prime = true;
		for (int n = 2; n < tempValue; n++) {
			if (tempValue%n == 0) {		//if division has a remainder it isn't prime
				prime = false;
			}
		}
		if (prime == true) {
			if (tempValue > 1)	//has to be greater than zero as negatives can't be prime
				count++;
		}
		temp = temp->next;				//get next node	
	}
	delete[] temp;	//delete temp 
	return count;
}

/*********************************************************************/
/*                       END CREATION NOW TEST                       */
/*********************************************************************/

/*********************************************************************
 ** Function: get integer
 ** Description: error checking function for integer inputs
 *********************************************************************/
int Linked_List::get_integer() {
	bool error = false;
	float x;
	string s;
	do {
		error = false;
		cout << "Enter a number: ";
		cin >> s;
		for (unsigned int i = 0; i < s.size(); i++) {
			if (!((s.at(i) >= '0' && s.at(i) <= '9') || s.at(i) == '-')) 
				error = true;
		}
		if (error == true)
			cout << "ERROR: Not valid, try again!" << endl;
	} while (error == 1);
	x = atoi(s.c_str());

	return x;
}

/*********************************************************************
 ** Function: play_game
 ** Description: runs test simulation
 *********************************************************************/
void Linked_List::play_game() {
	string another, again;
	bool error;
	do {
		do {
			int num = get_integer();
			push_back(num);
			cout << "Do you want another number(y or n): ";
			cin >> another;
		} while (another == "y" || another == "Y");
		string dir;
		do {
			error = false;
			cout << "Sort ascending or descending(a or d): ";
			cin >> dir;
			if (dir == "a" || dir == "A")
				sort_ascending();
			else if (dir == "d" || dir == "D")
				sort_descending();
			else {
				cout << "Not valid, try again" << endl;
				error = true;
			}
		} while (error == true);
		print();
		cout << "You have " << get_primes() << " prime number(s) in your list" << endl;
		cout << "Do you want to go again(y or n): ";
		cin >> again;
		if (again == "y" || again == "Y")
			clear();
	} while (again == "y" || again == "Y");
	cout << "Goodbye!" << endl;
	clear();
}
