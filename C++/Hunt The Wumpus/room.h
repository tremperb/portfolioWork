/*********************************************************************
** Program Filename: room.h
** Description: header file
*********************************************************************/

#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Room {
private:
	vector<vector<string>> grid;
	vector<vector<string>> copy;
	int count;
	int gold;
	int arrows;
	string debug;
public:
	Room();
	~Room();
	void get_intro();
	void original_grid();
	void play_game(int &size);
	void make_grid(int &size);
	void get_move();
	int get_char_start(int &size);
	void set_vector(vector<vector<string>> grid);
	vector<vector<string>> get_vector();
	void set_copy(vector<vector<string>> copy);
	vector<vector<string>> get_copy();
	void fill_grid(int &size);
	void fill_events(int &size);
	string get_char();
	void make_move(string &move);
	void north();
	void east();
	void south();
	void west();
	void update_grid();
	int get_x();
	int get_y();
	void set_count(const int& count);
	int get_count() const;
	void set_arrows(const int& arrows);
	int get_arrows() const;
	void set_gold(const int& gold);
	int get_gold() const;
	void set_debug(const string& debug);
	string get_debug() const;
	void get_encounter(string &type, int &x, int &y);
	void get_percept();
	void percept_north(int &x, int &y);
	void percept_east(int &x, int &y);
	void percept_south(int &x, int &y);
	void percept_west(int &x, int &y);
	void display_percept(string &mark);
	void get_response(int &out, int &x, int &y);
	void is_dead();
	void found_gold(int &x, int &y);
	void bats_effect();
	void get_escape();
	void arrow_north();
	void arrow_east();
	void arrow_south();
	void arrow_west();
	int check_hit(int &x, int &y);
	void check_arrows();
	void new_wumpus();
	int dead(int status);
};
#endif

