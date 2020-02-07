#include "room.h"
#include "event.h"
#include "gold.h"
#include "wumpus.h"
#include "pit.h"
#include "bats.h"
#include "escape.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>

using namespace std;

/*********************************************************************
** Function: Room
** Description: default constructor
*********************************************************************/
Room::Room() {
	srand(time(NULL));
	gold = 0;
	count = 0;
	arrows = 3;
}

/*********************************************************************
** Function: ~Room
** Description: default destructor
*********************************************************************/
Room::~Room() {
}

/*********************************************************************
** Function: get intro
** Description: displays intro
*********************************************************************/
void Room::get_intro() {
	cout << "| Welcome to Hunt the Wumpus! |" << endl;
	cout << "*******************************" << endl;
	cout << "The goal of this game if to find and kill the Wumpus!" << endl;
	cout << "You will be dropped off and a random point and I will give you 3 arrows to defeat the Wumpus" << endl;
	cout << "Upon defeating the Wumpus you must steal his gold and return to the drop off point for your evac" << endl;
	cout << "You may encounter traps upon the way so be careful and good luck!" << endl;
	cout << "Your current location on the map will be marked with a: '*'" << endl;
	cout << endl;
}

/*********************************************************************
** Function: get char start
** Description: gets random point
*********************************************************************/
int Room::get_char_start(int &size) {
	int x = rand() % size;	//gets random point the size of the grid

	return x;
}

/*********************************************************************
** Function: set vector
** Description: allows vector to be accessed
*********************************************************************/
void Room::set_vector(vector<vector<string>> grid) {
	this->grid = grid;
}

/*********************************************************************
** Function: get vector
** Description: allows vector to be accessed
*********************************************************************/
vector<vector<string>> Room::get_vector() {
	return grid;
}

/*********************************************************************
** Function: set copy
** Description: sets copy for grid to be used
*********************************************************************/
void Room::set_copy(vector<vector<string>> copy) {
	this->copy = copy;
}

/*********************************************************************
** Function: get copy
** Description: gets copy for grid to be used 
*********************************************************************/
vector<vector<string>> Room::get_copy() {
	return copy;
}

/*********************************************************************
** Function: set count
** Description: allows access to count
*********************************************************************/
void Room::set_count(const int& count) {
	this->count = count;
}

/*********************************************************************
** Function: get count
** Description: allows access to count
*********************************************************************/
int Room::get_count() const {
	return count;
}

/*********************************************************************
** Function: set arrows
** Description: allows access to arrows
*********************************************************************/
void Room::set_arrows(const int& arrows) {
	this->arrows = arrows;
}

/*********************************************************************
** Function: get arrows
** Description: allows access to arrows
*********************************************************************/
int Room::get_arrows() const {
	return arrows;
}

/*********************************************************************
** Function: set gold
** Description: allows access to gold
*********************************************************************/
void Room::set_gold(const int& gold) {
	this->gold = gold;
}

/*********************************************************************
** Function: get gold
** Description: allows access to gold
*********************************************************************/
int Room::get_gold() const {
	return gold;
}

/*********************************************************************
** Function: play game
** Description: calls function to play game
*********************************************************************/
void Room::play_game(int &size) {
	int x = 1;
	int dead_check = 0;
	get_intro();	//call needed function
	make_grid(size);
	original_grid();
	do{
		get_move();
		dead_check = dead(0);
	} while (dead_check == 0); //does until dead or escaped 
}

/*********************************************************************
** Function: set debug
** Description: allows access to dubug string
*********************************************************************/
void Room::set_debug(const string &debug) {
	this->debug = debug;
}

/*********************************************************************
** Function: get debug
** Description: allows access to dubug string
*********************************************************************/
string Room::get_debug() const {
	return debug;
}

/*********************************************************************
** Function: fill grid
** Description: fills the grid
*********************************************************************/
void Room::fill_grid(int &size) {
	string marker = "*";
	int x = get_char_start(size);	//get random spot for character start point
	int y = get_char_start(size);

	grid.resize(size);
	for (int i = 0; i < size; ++i)
		grid[i].resize(size);	//resize the grid to the user desired size
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid[i].size(); k++) {
			if (i == x && k == y)
				grid[i][k] = "*";	//if the spot set the location
			else
				grid[i][k] = " ";	//else make empty
		}
	}
	fill_events(size);	//now fill empty spots with events
}

/*********************************************************************
** Function: original grid
** Description: make copy of grid
*********************************************************************/
void Room::original_grid() {
	copy = grid;	//sets grid to the copy
}

/*********************************************************************
** Function: fill events
** Description: gets random spot for each event and stores in vector
*********************************************************************/
void Room::fill_events(int &size) {
	int retry = 0;
	string mark = " ";
	do {
		retry = 0;
		int x = get_char_start(size);
		int y = get_char_start(size);
		if (grid[x][y] == " ") {	//only if spot is empty
			mark = get_char();		//get the event marker
			if(mark != "q")
				grid[x][y] = mark;	//set that spot with the corresponding makrer
		}
		else {
			retry = 1;
		}
	} while (retry == 1);
	if(mark != "q")
		fill_events(size);	//go until all events have been filled
}

/*********************************************************************
** Function: get char
** Description: make and displays the grid
*********************************************************************/
string Room::get_char() {
	string mark;
	static int count=0;
	if (count == 0)
		mark = "w";
	else if (count == 1 || count == 2)	//get necessary amount for each event
		mark = "p";
	else if (count == 3 || count == 4)
		mark = "b";
	else if (count == 5)
		mark = "g";
	else {
		mark = "q";	//return q if done
		count = -1;
	}
	count++;
	return mark;
}

/*********************************************************************
** Function: make grid
** Description: make and displays the grid
*********************************************************************/
void Room::make_grid(int &size) {
	fill_grid(size);	//fill the vector
	
	for (int i = 0; i < size; i++) {
		for (unsigned int k = 0; k < size; k++) {
			cout << "+-----";
		}
		cout << "+" << endl;
		for (unsigned int k = 0; k < size; k++) {
			string mark = grid[i][k];
			cout << "|" << "  ";
			if (debug == "true")	//if debug show all
				cout << mark;
			else {
				if (mark == "*")
					cout << mark;	//else only show player
				else
					cout << " ";
			}
			cout << "  ";
			
		}
		cout << "|" << endl;

	}
	for (unsigned int i = 0; i < size; i++) {
		cout << "+-----";
	}
	cout << "+" << endl;
}

/*********************************************************************
** Function: get percept
** Description: gets percept for players poistion
*********************************************************************/
void Room::get_percept() {
	int x, y;
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid.size(); k++) {
			if (grid[i][k] == "*") {
				x = i;
				y = k;	//gets players current position
			}
		}
	}
	percept_north(x, y);	//calls function
	percept_east(x, y);
	percept_south(x, y);
	percept_west(x, y);
}

/*********************************************************************
** Function: percept north
** Description: checks for percept in that direction
*********************************************************************/
void Room::percept_north(int &x, int &y) {
	string mark = " ";
	if (x - 1 >= 0) {
		mark = grid[x - 1][y];
		if (mark == " " || mark == "e") {
		}
		else {
			display_percept(mark);
		}
	}
}

/*********************************************************************
** Function: percept east
** Description: checks for percept in that direction
*********************************************************************/
void Room::percept_east(int &x, int &y) {
	string mark = " ";
	if (y + 1 < grid.size()) {
		mark = grid[x][y+1];
		if (mark == " " || mark == "e") {
		}
		else {
			display_percept(mark);
		}
	}
}

/*********************************************************************
** Function: percept south
** Description: checks for percept in that direction
*********************************************************************/
void Room::percept_south(int &x, int &y) {
	string mark = " ";
	if (x + 1 < grid.size()) {
		mark = grid[x + 1][y];
		if (mark == " " || mark == "e") {
		}
		else {
			display_percept(mark);
		}
	}
}

/*********************************************************************
** Function: percept west
** Description: checks for percept in that direction
*********************************************************************/
void Room::percept_west(int &x, int &y) {
	string mark = " ";
	if (y - 1 >= 0) {
		mark = grid[x][y-1];	//mark that string
		if (mark == " " || mark == "e") {
		}
		else {
			display_percept(mark);	//if it is an event display the warning
		}
	}
}

/*********************************************************************
** Function: display percept
** Description: display warnings for event w/ polymorphesm
*********************************************************************/
void Room::display_percept(string &mark) {
	Event *e;	//event pointer
	if (mark == "w")
		e = new Wumpus;	//point to wumpus warning
	else if (mark == "g")
		e = new Gold;
	else if (mark == "p")
		e = new Pit;
	else
		e = new Bats;
	e->percept();		//call that function
	if(e != NULL)
		delete e;
}

/*********************************************************************
** Function: get move
** Description: gets move from player
*********************************************************************/
void Room::get_move() {
	string direction;
	int error;
	get_percept();
	do {
		error = 0;
		cout << endl;
		cout << "Which way would you like to move? or you can shoot an arrow" << endl;
		cout << "Available movement options are: " << endl;
		cout << "w = north, d = east, s = south, a = west, r = arrow" << endl;
		cout << "If you would like to shoot an arrow. You can do so by enter a space prior to your direction!" << endl;
		cout << "Input: ";
		getline(cin, direction);
		if (direction == "w" || direction == "d" || direction == "s" || direction == "a") {
			cout << "You chose to move" << endl;
		}
		else if (direction == " w" || direction == " d" || direction == " s" || direction == " a") {	
			if (arrows == 0) {
				cout << "Sorry you are out of arrows" << endl;
				cout << "All you can do now is find the gold and escape" << endl;
				error = 1;
			}
			else {
				cout << "You chose to fire an arrow" << endl;
			}
		}
		else {
			cout << "Not valid, try again" << endl;
			error = 1;
		}
	} while (error == 1);	//while invalid

	make_move(direction);	//now make the corresponding move
}

/*********************************************************************
** Function: make move
** Description: calls response to move
*********************************************************************/
void Room::make_move(string &move) {
	
	if (move == "w") {
		north();	//call corresponding functions
	}
	else if (move == "d") {
		east();
	}
	else if (move == "s") {
		south();
	}
	else if (move == "a") {
		west();
	}
	else if (move == " w") {
		arrow_north();	//it an arrow so shoot it in that direction
	}
	else if (move == " d") {
		arrow_east();
	}
	else if (move == " s") {
		arrow_south();
	}
	else if (move == " a") {
		arrow_west();
	}
	
	
}

/*********************************************************************
** Function: check hit
** Description: checks to see if the arrow hit the wumpus
*********************************************************************/
int Room::check_hit(int &x, int &y) {

	if (grid[x][y] == "w") {	//if it is the wumpus
		cout << endl;
		cout << "You have landed your arrow!" << endl;
		cout << "The wumpus is now dead!" << endl;
		grid[x][y] = " ";	//if dead replce spot to be empty
		return 1;		//return hit
	}
	return 0;
}

/*********************************************************************
** Function: arrow north
** Description: gets action for arrow in that direction
*********************************************************************/
void Room::arrow_north() {
	int x = get_x();	//gets current location
	int y = get_y();
	int hit = 0;
	if (x - 1 >= 0) {	//for first wall 
		x = x - 1;
		hit = check_hit(x, y);	//check if hit	
		if (x - 1 >= 0 && hit == 0) {	//if not try next wall if they have not reached max
			x = x - 1;
			hit = check_hit(x, y);
			if (x - 1 >= 0 && hit == 0) {	//last chance to check
				x = x - 1;
				hit = check_hit(x, y);
			}
		}

	}
	if (hit != 1) {	//if it still never hit they missed
		cout << endl;
		cout << "You missed!" << endl;
		arrows--;	//decrease arrow count
		check_arrows();
		new_wumpus();
	}
	update_grid();
}

/*********************************************************************
** Function: arrow east
** Description: gets action for arrow in that direction
*********************************************************************/
void Room::arrow_east() {
	int x = get_x();
	int y = get_y();
	int hit = 0;
	if (y + 1 < grid.size()) {
		y = y + 1;
		hit = check_hit(x, y);
		if (y + 1 < grid.size() && hit == 0) {
			y = y + 1;
			hit = check_hit(x, y);
			if (y + 1 < grid.size() && hit == 0) {
				y = y + 1;
				hit = check_hit(x, y);
			}
		}
	}
	if (hit != 1) {
		cout << endl;
		cout << "You missed!" << endl;
		arrows--;
		check_arrows();
		new_wumpus();
	}
	update_grid();
}

/*********************************************************************
** Function: arrow south
** Description: gets action for arrow in that direction
*********************************************************************/
void Room::arrow_south() {
	int x = get_x();
	int y = get_y();
	int hit = 0;
	if (x + 1 < grid.size()) {
		x = x + 1;
		hit = check_hit(x, y);
		if (x + 1 < grid.size() && hit == 0) {
			x = x + 1;
			hit = check_hit(x, y);
			if (x + 1 < grid.size() && hit == 0) {
				x = x + 1;
				hit = check_hit(x, y);
			}
		}
	}
	if (hit != 1) {
		cout << endl;
		cout << "You missed!" << endl;
		arrows--;
		check_arrows();
		new_wumpus();
	}
	update_grid();
}

/*********************************************************************
** Function: arrow west
** Description: gets action for arrow in that direction
*********************************************************************/
void Room::arrow_west() {
	int x = get_x();
	int y = get_y();
	int hit = 0;
	if (y - 1 >= 0) {
		y = y - 1;
		hit = check_hit(x, y);
		if (y - 1 >= 0 && hit == 0) {
			y = y - 1;
			hit = check_hit(x, y);
			if (y - 1 >= 0 && hit == 0) {
				y = y - 1;
				hit = check_hit(x, y);
			}
		}

	}
	if (hit != 1) {
		cout << endl;
		cout << "You missed!" << endl;
		arrows--;
		check_arrows();
		new_wumpus();
	}
	update_grid();
}

/*********************************************************************
** Function: new wumpus
** Description: gets wumpus response from missed arrow
*********************************************************************/
void Room::new_wumpus() {
	int chance = rand() % 4 + 1;	//1-3 chance it moves
	int count = 0;
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid.size(); k++) {
			if (grid[i][k] == "w")
				count = 1;			//checks to be sure there is still a wumpus
		}
	}
	if (count == 1) {
		if (chance == 4) {
			cout << "Luckily the Wumpus didnt hear you" << endl;
		}
		else {
			int empty = 0;
			cout << "The wumpus heard you and has now moved" << endl;
			do {
				int size = grid.size();
				int x = get_char_start(size);	//get new position
				int y = get_char_start(size);
				if (grid[x][y] == " ") {		//only if empty room
					empty = 1;
					for (unsigned int i = 0; i < grid.size(); i++) {
						for (unsigned int k = 0; k < grid.size(); k++) {
							if (grid[i][k] == "w")
								grid[i][k] = " ";	//set previous location to blank
						}
					}
					grid[x][y] = "w";	//set new wumpus location
				}
				else
					empty = 0;
			} while (empty == 0);
		}
	}
}

/*********************************************************************
** Function: check arrows
** Description: checks arrow count as you only get 3
*********************************************************************/
void Room::check_arrows() {
	if (arrows == 0) {
		cout << "You are out of arrows!" << endl;	//checks arrow count
	}
}

/*********************************************************************
** Function: get x
** Description: gets player x location
*********************************************************************/
int Room::get_x() {
	int x=0;
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid.size(); k++) {
			if (grid[i][k] == "*") {
				x = i;
			}
		}
	}
	return x;
}

/*********************************************************************
** Function: get y
** Description: gets player y location
*********************************************************************/
int Room::get_y() {
	int y=0;
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid.size(); k++) {
			if (grid[i][k] == "*") {
				y = k;	//if match for player location
			}
		}
	}
	return y;
}

/*********************************************************************
** Function: get encounter
** Description: gets encounter from class with polymorphesim
*********************************************************************/
void Room::get_encounter(string &type, int &x, int &y) {
	Event *e;		//creats event pointer
	cout << endl;
	if (type == "g")
		e = new Gold;	//points to corresponding event
	else if (type == "w")
		e = new Wumpus;
	else if (type == "p")
		e = new Pit;
	else if (type == "b")
		e = new Bats;
	else
		e = new Escape;
	
	int out = e->encounter();	//call event encounter
	if(e != NULL)
		delete e;
	get_response(out, x, y);
}

/*********************************************************************
** Function: get response
** Description: gets response for events
*********************************************************************/
void Room::get_response(int &out, int &x, int &y) {
	if (out == 1) {
		is_dead();
	}
	else if (out == 2) {
		found_gold(x, y);
	}
	else if (out == 3) {
		bats_effect();
		grid[x][y] = " ";
	}
	else {
		get_escape();
	}
}

/*********************************************************************
** Function: get escape
** Description: get action for escape
*********************************************************************/
void Room::get_escape() {
	int x, y;
	if (gold == 1) {	//if gold is picked up you can leave
		cout << "You have got the gold and are now able to leave" << endl;
		cout << "Good job! This game will now end!" << endl;
		dead(1);
	}
	else {
		cout << "You cannot escape until you find the gold!" << endl;
		cout << "Now you are confused and travel to a random empty room" << endl;
		int found = 0;
		int size = grid.size();
		do {
			x = get_char_start(size);		//dont have gold now confused 
			y = get_char_start(size);		//put character to random spot
			if (grid[x][y] == " ") {
				found = 1;
			}
			else
				found = 0;
		} while (found == 0);				//do it until the spot is empty
		grid[x][y] = "*";
	}
}

/********************************************************************
** Function: dead
** Description: checks to see if dead
********************************************************************/
int Room::dead(int status) {
	static int new_stat = 0;	//initialized as zero for the first time
	new_stat = new_stat + status;	//adds them together taking 1 if dead and 0 if not

	return new_stat;
}

/*********************************************************************
** Function: bats effect
** Description: gets action for bats
*********************************************************************/
void Room::bats_effect() {
	int size = grid.size();
	string mark;
	int x = get_char_start(size);	//get random points
	int y = get_char_start(size);
	if (grid[x][y] == " ")
		grid[x][y] = "*";			//if empty just set the *
	else {
		mark = grid[x][y];
		get_encounter(mark, x, y);	//otherwise there is an ecounter
	}
}

/*********************************************************************
** Function: found gold
** Description: marks gold as found
*********************************************************************/
void Room::found_gold(int &x, int &y) {
	gold = 1;			//increase gold to 1 to denote found
	grid[x][y] = "*";	//replace gold icon with plyer mark
}

/*********************************************************************
** Function: is dead
** Description: the player is dead now see if they want to continue
*********************************************************************/
void Room::is_dead() {
	string again, map;
	cout << "You have died!" << endl;
	cout << "Would you like to go again(yes/no)? ";
	cin >> again;
	if (again == "yes") {
		count = -1;
		cout << "Would you like the same map or a random map? (S/R) ";
		cin >> map;
		if (map == "S" || map == "s") {
			grid = copy;		//if same new grid is the copy of last
		}
		else {
			int size = grid.size();		//new grid so fill new grid and then save copy
			fill_grid(size);
			original_grid();
		}
	}
	else {
		cout << "This game will now end, goodbye" << endl;
		dead(1);	//leave so exit
	}
}

/*********************************************************************
** Function: north
** Description: gets action for north direction
*********************************************************************/
void Room::north() {
	int x = get_x();		//gets current position
	int y = get_y();
	if (x - 1 < 0) {		//check to make sure in vector bounds
		cout << endl;
		cout << "ERROR! You can't go that way!" << endl;
		cout << endl;
		goto error;			//skip all and just go to error
	}
	if (grid[x-1][y] == " ") {		//x-1 for north like grid(accidentally mixed x and y but same thing)
		if (count == 0)
			grid[x][y] = "e";		//if count equals 0 its the first move so mark the escape point
		else
			grid[x][y] = " ";
		grid[x - 1][y] = "*";
		
	}
	else {
		if (count == 0)
			grid[x][y] = "e";
		else
			grid[x][y] = " ";
		x = x - 1;
		string enc = grid[x][y];		//gets the character encounter
		get_encounter(enc, x, y);		//calls function to get response
	}
error:
	int d = dead(0);
	if(d == 0)
		update_grid();					//updates grid
	count++;
}

/*********************************************************************
** Function: east
** Description: gets action for east direction
*********************************************************************/
void Room::east() {
	int x = get_x();
	int y = get_y();
	if (y + 1 >= grid.size()) {
		cout << endl;
		cout << "ERROR! You can't go that way!" << endl;
		cout << endl;
		goto error;
	}
	if (grid[x][y+1] == " ") {			//y+1 to go east
		if (count == 0)
			grid[x][y] = "e";
		else
			grid[x][y] = " ";
		grid[x][y+1] = "*";

	}
	else {
		if (count == 0)
			grid[x][y] = "e";
		else
			grid[x][y] = " ";
		y = y + 1;
		string enc = grid[x][y];
		get_encounter(enc, x, y);
	}
error:
	int d = dead(0);
	if (d == 0)
		update_grid();
	count++;
}

/*********************************************************************
** Function: south
** Description: gets action for south direction
*********************************************************************/
void Room::south() {
	int x = get_x();
	int y = get_y();
	if (x + 1 >= grid.size()) {
		cout << endl;
		cout << "ERROR! You can't go that way!" << endl;
		cout << endl;
		goto error;
	}
	if (grid[x+1][y] == " ") {			//x+1 to go south
		if (count == 0)
			grid[x][y] = "e";
		else
			grid[x][y] = " ";
		grid[x+1][y] = "*";

	}
	else {
		if (count == 0)
			grid[x][y] = "e";
		else
			grid[x][y] = " ";
		x = x + 1;
		string enc = grid[x][y];
		get_encounter(enc, x, y);
	}
error:
	int d = dead(0);
	if(d == 0)
		update_grid();
	count++;
}

/*********************************************************************
** Function: west
** Description: gets action for west direction
*********************************************************************/
void Room::west() {
	int x = get_x();
	int y = get_y();
	if (y - 1 < 0) {
		cout << endl;
		cout << "ERROR! You can't go that way!" << endl;
		cout << endl;
		goto error;
	}
	if (grid[x][y-1] == " ") {			//y-1 to go west
		if (count == 0)
			grid[x][y] = "e";
		else
			grid[x][y] = " ";
		grid[x][y-1] = "*";

	}
	else {
		if (count == 0)
			grid[x][y] = "e";
		else
			grid[x][y] = " ";
		y = y - 1;
		string enc = grid[x][y];
		get_encounter(enc, x, y);
	}
error:
	int d = dead(0);
	if(d == 0)
		update_grid();
	count++;
}

/*********************************************************************
** Function: update grid
** Description: updates player grid
*********************************************************************/
void Room::update_grid() {
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int k = 0; k < grid.size(); k++) {
			cout << "+-----";
		}
		cout << "+" << endl;
		for (unsigned int k = 0; k < grid.size(); k++) {
			string mark = grid[i][k];
			cout << "|" << "  ";
			if (debug == "true")		//if in debug mode display all marks
				cout << mark;
			else {
				if (mark == "*")		//otherwise only show player position
					cout << mark;
				else
					cout << " ";
			}
			cout << "  ";

		}
		cout << "|" << endl;

	}
	for (unsigned int i = 0; i < grid.size(); i++) {
		cout << "+-----";
	}
	cout << "+" << endl;
}
