/******************************************************
** Program: zoo.cpp
** Author: Brayden Tremper
** Date: 05/12/2019
** Description: Creates zoo game getting various responses
and outputting them accordingly. 
** Input: Various inputs from user to create their zoo
** Output: Outputs responses and the list of animals w/ age
******************************************************/

#include "zoo.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

/*********************************************************************
** Function: zoo
** Description: zoo constructor, intializes starting values
*********************************************************************/
Zoo::Zoo() {
	total_monkeys = 1;
	total_meerkats = 1;
	total_otters = 1;
	balance = 100000;
	foodCost = 40;
}

/*********************************************************************
** Function: ~zoo
** Description: zoo destructor, deletes allocated memory
*********************************************************************/
Zoo::~Zoo() {
	for (int i = 0; i < 3; i++) {
		delete[] animals[i];
	}
	delete[] animals;
}

/*********************************************************************
** Function: set total monkeys
** Description: sets value to be used throughout class
*********************************************************************/
void Zoo::set_total_monkeys(const int &total_monkeys) {
	this->total_monkeys = total_monkeys;
}

/*********************************************************************
** Function: get total monkeys
** Description: gets value to be used throughout class
*********************************************************************/
int Zoo::get_total_monkeys() const {
	return total_monkeys;
}

/*********************************************************************
** Function: set total meerkats
** Description: sets value to be used throughout class
*********************************************************************/
void Zoo::set_total_meerkats(const int &total_meerkats) {
	this->total_meerkats = total_meerkats;
}

/*********************************************************************
** Function: get total meerkats
** Description: gets value to be used throughout class
*********************************************************************/
int Zoo::get_total_meerkats() const {
	return total_meerkats;
}

/*********************************************************************
** Function: set total otters
** Description: sets value to be used throughout class
*********************************************************************/
void Zoo::set_total_otters(const int &total_otters) {
	this->total_otters = total_otters;
}

/*********************************************************************
** Function: get total otters
** Description: gets value to be used throughout class
*********************************************************************/
int Zoo::get_total_otters() const {
	return total_otters;
}

/*********************************************************************
** Function: set balance
** Description: sets value to be used throughout class
*********************************************************************/
void Zoo::set_balance(const float& balance) {
	this->balance = balance;
}

/*********************************************************************
** Function: get balance
** Description: gets value to be used throughout class
*********************************************************************/
float Zoo::get_balance() const {
	return balance;
}

/*********************************************************************
** Function: set food cost
** Description: sets value to be used throughout class
*********************************************************************/
void Zoo::set_foodCost(const float& foodCost) {
	this->foodCost = foodCost;
}

/*********************************************************************
** Function: get food cost
** Description: gets value to be used throughout class
*********************************************************************/
float Zoo::get_foodCost() const {
	return foodCost;
}

/*********************************************************************
** Function: play game
** Description: calls functions to play game continuing until the would like to quit
*********************************************************************/
void Zoo::play_game() {
	string again;
	intro();
	
	create_animal();	//creates animal array 
	do {
		get_animal();
		special_event();
		get_revenue();
		get_food_amount();
		increment_age();
		display_animals();
		cout << endl;
		cout << "Would you like to continue to the next week?(yes or no) ";
		cin >> again;  //continues until the wish to quit
	} while (again == "yes" || again == "Yes" || again == "YES");
	cout << "Thanks for playing! Goodbye" << endl;
}

/*********************************************************************
** Function: intro
** Description: displays introduction to program
*********************************************************************/
void Zoo::intro() {
	cout << "Welcome to Zoo Tycoon!" << endl;
	cout << "The goal of this game is to maintain a zoo!" << endl;
	cout << "You must do so by purchasing animals and taking care of them" << endl;
	cout << "In order for the game to continue you must maintain a positive balance." << endl;
	cout << "I will give you $100,000 to start with and one of each animal!" << endl;
	cout << endl;
}

/*********************************************************************
** Function: get animal
** Description: gets animals the wish to purchase 0-2
*********************************************************************/
void Zoo::get_animal() {
	cout << endl;
	string buy;
	string a;
	int error, cost=0;
	cout << "Would you like to buy an animal(Yes/No)? ";
	cin >> buy;
	if (buy == "Yes" || buy == "yes") {
		do {
			error = 0;
			cout << "Which Animal would you like to buy(Monkey, Otter, or Meerkat)? ";
			cin >> a;
			if (a == "Monkey" || a == "monkey") {
				int num = get_num(a);	//calls function to get number maaking sure valid
				cost = num * 15000;		//multiplies that number by the price of the animal
				add_adult_monkey(num);	//calls function to add the animal to the array
			}
			else if (a == "Otter" || a == "otter") {
				int num = get_num(a);
				cost = num * 5000;
				add_adult_otter(num);
			}
			else if (a == "Meerkat" || a == "meerkat") {
				int num = get_num(a);
				cost = num * 500;
				add_adult_meerkat(num);
			}
			else {
				cout << "Not valid, try again" << endl;
				error = 1;
			}
		} while (error == 1);
	}
	else {
		cout << "You have decided not to purchase any animals this week" << endl;
	}
	balance -= cost;	//subtracts cost of animals from player balance
	check_balance();	//checks balance to be sure not negative
}

/*********************************************************************
** Function: add adult monkey
** Description: adds an adult monkey to the array by the number purchased
*********************************************************************/
void Zoo::add_adult_monkey(int &num) {
	total_monkeys += num;	//updates monkey
	Animal *temp = new Monkey[total_monkeys];	//creates temporary array

	for (int i = 0; i < total_monkeys - num; i++) {
		temp[i] = animals[0][i];	//stores original values in temp array
	}
	for (int i = total_monkeys - num; i < total_monkeys; i++) {
		temp[i] = Monkey(96);		//stores new values in temp with age of 96
	}
	delete[] animals[0];
	animals[0] = new Monkey[total_monkeys];	//calls new array for monkey
	for (int i = 0; i < total_monkeys; i++) {
		animals[0][i] = temp[i];			//stores values from temp in original array
	}
	
	delete[] temp; //deletes the temporary array
}

/*********************************************************************
 ** Function: add adult otter
 ** Description: adds an adult otter to the array by the number purchased
 **note same layout as monkey so no new comments
 *********************************************************************/
void Zoo::add_adult_otter(int &num) {
	total_otters += num;
	Animal *temp = new Otter[total_otters];

	for (int i = 0; i < total_otters - num; i++) {
		temp[i] = animals[1][i];
	}
	for (int i = total_otters - num; i < total_otters; i++) {
		temp[i] = Otter(96);
	}
	delete[] animals[1];
	animals[1] = new Otter[total_otters];
	for (int i = 0; i < total_otters; i++) {
		animals[1][i] = temp[i];
	}

	delete[] temp; //if memory leak check here
}

/*********************************************************************
 ** Function: add adult meerkat
 ** Description: adds an adult meerkat to the array by the number purchased
 **note same layout as monkey so no new comments
 *********************************************************************/
void Zoo::add_adult_meerkat(int &num) {
	total_meerkats += num;
	Animal *temp = new Meerkat[total_meerkats];

	for (int i = 0; i < total_meerkats - num; i++) {
		temp[i] = animals[2][i];
	}
	for (int i = total_meerkats - num; i < total_meerkats; i++) {
		temp[i] = Meerkat(96);
	}
	delete[] animals[2];
	animals[2] = new Meerkat[total_meerkats];
	for (int i = 0; i < total_meerkats; i++) {
		animals[2][i] = temp[i];
	}

	delete[] temp; //if memory leak check here
}

/*********************************************************************
 ** Function: create animal
 ** Description: creates a 2d array of animals
 *********************************************************************/
void Zoo::create_animal() {
	animals = new Animal*[3]; //animal w/ 3 options monkey, otter, meerkat
	animals[0] = new Monkey[total_monkeys];
	animals[1] = new Otter[total_otters];
	animals[2] = new Meerkat[total_meerkats];
	for (int i = 0; i < total_monkeys; i++) {
		animals[0][i] = Monkey(96);				//monkey with age as arguments sets age to 2 aka 96 weeks
	}
	for (int i = 0; i < total_otters; i++) {
		animals[1][i] = Otter(96);
	}
	for (int i = 0; i < total_meerkats; i++) {
		animals[2][i] = Meerkat(96);
	}
}

/*********************************************************************
 ** Function: check balance
 ** Description: checks balance against 0
 *********************************************************************/
void Zoo::check_balance() {
	if (balance <= 0) {
		cout << "You have gone bankrupt! You Lose!" << endl;
		cout << "This game is now over!" << endl;
		exit(0);
	}
}

/*********************************************************************
 ** Function: get num
 ** Description: get number of animals with error checking
 *********************************************************************/
int Zoo::get_num(string &type) {
	int num, error;
	string x;
	do {
		cout << "How many " << type << "'s would you like to purchase(1 or 2): ";
		cin >> x;
		if (x == "1" || x == "2") {
			error = 0;
			num = atoi(x.c_str()); //string to int
		}
		else {
			cout << "Not valid, try again" << endl;
			error = 1;
		}

	} while (error == 1);

	return num;
}

/*********************************************************************
 ** Function: special event
 ** Description: random # 1-4 displays according event
 *********************************************************************/
void Zoo::special_event() {
	cout << endl;
	srand(time(NULL));
	int roll = rand() % 4 + 1;	//generates random number 1-4
	switch (roll) {
		case 1: 
			get_sick();	//call sick function
			break;
		case 2: 
			get_baby();	//call baby function
			break;
		case 3: 
			random_bonus();	//call bonus function
			break;
		case 4: cout << "No special event occured" << endl;
				  break;
	}
	cout << endl;
	cout << "Enter something to continue: ";
	string in;
	cin >> in;	//pauses game waiting for user response
}

void Zoo::random_bonus() {
	srand(time(NULL));
	int bonus = rand() % 401 + 300; //generates random number from 300-700

	cout << "A boom in attendance has occured you will receive a bonus of " << bonus;
	cout << " for every monkey!" << endl;
	cout << endl;
	if (total_monkeys == 0) {
		cout << "However, you have no monkeys thus will not receive this bonus." << endl;
	}
	else {
		int total_bonus = total_monkeys * bonus;	//gets bonus for every monkey
		balance += total_bonus;	//updates balance with bonus rest of weekly payout will be paid later
		cout << "Your balance is now " << balance << endl;
		cout << "You will receive the rest of your revenue on payday!" << endl;
	}
}

/*********************************************************************
 ** Function: get baby
 ** Description: random animal has baby if they are present and of age
 *********************************************************************/
void Zoo::get_baby() {
	int roll = get_roll(); //gets roll for animal type
	int nextRoll;
	switch (roll) {
		case 0:
			cout << "A Monkey has had a baby!" << endl;
			nextRoll = check_roll(roll);	//gets roll for which monkey of age will have baby
			add_monkey(roll, nextRoll);		//adds that monkey to the array
			break;
		case 1:
			cout << "An Otter has had two babies!" << endl;
			nextRoll = check_roll(roll);
			add_otter(roll, nextRoll);
			break;
		case 2:
			cout << "A Meerkat has had five babies!" << endl;
			nextRoll = check_roll(roll);
			add_meerkat(roll, nextRoll);
			break;
	}
}

/*********************************************************************
 ** Function: add monkey
 ** Description: adds the according number of babies to the array with
 the age starting at 0 weeks
 *********************************************************************/
void Zoo::add_monkey(int &roll, int &nextRoll) {
	total_monkeys += 1;	//updates total with 1 baby
	Animal *temp = new Monkey[total_monkeys];

	for (int i = 0; i < total_monkeys - 1; i++) {
		temp[i] = animals[0][i];	//stores in temp array
	}
	for (int i = total_monkeys-1; i < total_monkeys; i++) {
		temp[i] = Monkey(0);	//adding the baby to the temp array
	}
	delete[] animals[0];
	animals[0] = new Monkey[total_monkeys];
	for (int i = 0; i < total_monkeys; i++) {
		animals[0][i] = temp[i];	//puts the temp back in animal
	}

	delete[] temp; //delets temp array
}

/*********************************************************************
 ** Function: add otter
 ** Description: adds the according number of babies to the array with
 the age starting at 0 weeks
 *Note: same at monkey so no comments
 *********************************************************************/
void Zoo::add_otter(int &roll, int &nextRoll) {
	total_otters += 2;
	Animal *temp = new Otter[total_otters];

	for (int i = 0; i < total_otters - 2; i++) {
		temp[i] = animals[1][i];
	}
	for (int i = total_otters - 2; i < total_otters; i++) {
		temp[i] = Otter(0);
	}
	delete[] animals[1];
	animals[1] = new Otter[total_otters];
	for (int i = 0; i < total_otters; i++) {
		animals[1][i] = temp[i];
	}

	delete[] temp; //if memory leak check here
}

/*********************************************************************
 ** Function: add meerkat
 ** Description: adds the according number of babies to the array with
 the age starting at 0 weeks
 *********************************************************************/
void Zoo::add_meerkat(int &roll, int &nextRoll) {
	total_meerkats += 5;
	Animal *temp = new Meerkat[total_meerkats];

	for (int i = 0; i < total_meerkats - 5; i++) {
		temp[i] = animals[2][i];
	}
	for (int i = total_meerkats - 5; i < total_meerkats; i++) {
		temp[i] = Meerkat(0);
	}
	delete[] animals[2];
	animals[2] = new Meerkat[total_meerkats];
	for (int i = 0; i < total_meerkats; i++) {
		animals[2][i] = temp[i];
	}

	delete[] temp; //if memory leak check here
}

/*********************************************************************
 ** Function: get roll
 ** Description: gets roll for animal type to have baby
 *********************************************************************/
int Zoo::get_roll() {
	srand(time(NULL));
	int available = 0, roll;
	do {
		roll = rand() % 3;	//random roll
		if (roll == 0) {
			for (int i = 0; i < total_monkeys; i++) {
				if (animals[0][i].get_age() >= 96) {	//checks to be sure above age
					available = 1;	//marks available
				}
			}
		}
		else if (roll == 1) {
			for (int i = 0; i < total_otters; i++) {
				if (animals[1][i].get_age() >= 96) {
					available = 1;
				}
			}
		}
		else if (roll == 2) {
			for (int i = 0; i < total_meerkats; i++) {
				if (animals[2][i].get_age() >= 96) {
					available = 1;
				}
			}
		}

	} while (available == 0);	//continues until available animal is found

	return roll;
}

/*********************************************************************
 ** Function: sick roll
 ** Description: finds roll to get animal type for being sick
 *Note: same as baby roll but no age requirement
 *********************************************************************/
int Zoo::sick_roll() {
	srand(time(NULL));
	int available = 0, roll;
	do {
		roll = rand() % 3;	//random rolls
		if (roll == 0) {
			for (int i = 0; i < total_monkeys; i++) {
				if (animals[0][i].get_age() >= 0) {	//if any animal is present
					available = 1;
				}
			}
		}
		else if (roll == 1) {
			for (int i = 0; i < total_otters; i++) {
				if (animals[1][i].get_age() >= 0) {
					available = 1;
				}
			}
		}
		else if (roll == 2) {
			for (int i = 0; i < total_meerkats; i++) {
				if (animals[2][i].get_age() >= 0) {
					available = 1;
				}
			}
		}

	} while (available == 0);

	return roll;	//returns the roll of the corresponding animal type
}

/*********************************************************************
 ** Function: check sick roll
 ** Description: according to first roll then rolls again to get specific animal
 *NOTE: same system as before so no new comments
 *********************************************************************/
int Zoo::check_sick_roll(int &roll) {
	srand(time(NULL));
	int nextRoll, good = 0;
	if (roll == 0) {
		do {
			nextRoll = rand() % total_monkeys;
			if (animals[0][nextRoll].get_age() >= 0) {
				good = 1;
			}
		} while (good == 0);
	}
	else if (roll == 1) {
		do {
			nextRoll = rand() % total_otters;
			if (animals[1][nextRoll].get_age() >= 0) {
				good = 1;
			}
		} while (good == 0);
	}
	else if (roll == 2) {
		do {
			nextRoll = rand() % total_meerkats;
			if (animals[2][nextRoll].get_age() >= 0) {
				good = 1;
			}
		} while (good == 0);
	}

	return nextRoll;
}

/*********************************************************************
 ** Function: get sick
 ** Description: gets random animal sick an calls function to heal animal
 *********************************************************************/
void Zoo::get_sick() {
	int roll = sick_roll();
	int nextRoll;
	switch (roll) {
		case 0: 
			cout << "A Monkey has gotten sick! This will cost $7500" << endl;
			nextRoll = check_sick_roll(roll);	//gets specific animal
			fix_sick_animal(roll, nextRoll);	//call function to either pay or lose animal
			break;
		case 1: 
			cout << "An Otter has gotten sick! This will cost $2500" << endl;
			nextRoll = check_sick_roll(roll);
			fix_sick_animal(roll, nextRoll);
			break;
		case 2: 
			cout << "A Meerkat has gotten sick! This will cost $250" << endl;
			nextRoll = check_sick_roll(roll);
			fix_sick_animal(roll, nextRoll);
			break;
	}
}

/*********************************************************************
 ** Function: check roll
 ** Description: checks roll for baby function getting specific animal
 *********************************************************************/
int Zoo::check_roll(int &roll) {
	srand(time(NULL));
	int nextRoll, good = 0;
	if (roll == 0) {
		do {
			nextRoll = rand() % total_monkeys;
			if (animals[0][nextRoll].get_age() >= 96) {
				good = 1;	//if greater than 96weeks(2 years)
			}
		} while (good == 0);
	}
	else if (roll == 1) {
		do {
			nextRoll = rand() % total_otters;
			if (animals[1][nextRoll].get_age() >= 96) {
				good = 1;
			}
		} while (good == 0);
	}
	else if (roll == 2) {
		do {
			nextRoll = rand() % total_meerkats;
			if (animals[2][nextRoll].get_age() >= 96) {
				good = 1;
			}
		} while (good == 0);
	}

	return nextRoll;
}

/*********************************************************************
 ** Function: fix sick animal
 ** Description: heals the sick animal if enough in balance otherwise animal dies
 *********************************************************************/
void Zoo::fix_sick_animal(int &roll, int &nextRoll) {
	int cost;
	if (roll == 0) {
		if (animals[0][nextRoll].get_age() <= 5) {
			cout << "A baby got sick!" << endl;
			cost = 15000;	//baby costs twice as much
		}
		else 
			cost = 7500;	//adult price
		if (cost <= balance) {
			balance -= cost;	//subtrcts from balance if enough
			cout << "The cost to heal the Monkey has been subtracted from you account." << endl;
			cout << "Your new balance is: " << balance << endl;
		}
		else {
			cout << "You dont have enough to fix this monkey!" << endl;
			cout << "Your animal has now died!" << endl;
			remove_animal(roll, nextRoll);	//not enough so calls function to remove that animal
		}
	}
	else if (roll == 1) {
		if (animals[1][nextRoll].get_age() <= 5) {
			cout << "A baby got sick!" << endl;
			cost = 1000;
		}
		else
			cost = 500;
		if (cost <= balance) {
			balance -= cost;
			cout << "The cost to heal the Otter has been subtracted from you account." << endl;
			cout << "Your new balance is: " << balance << endl;
		}
		else {
			cout << "You dont have enough to fix this monkey!" << endl;
			cout << "Your animal has now died!" << endl;
			remove_animal(roll, nextRoll);
		}
	}
	else if (roll == 2) {
		if (animals[2][nextRoll].get_age() <= 5) {
			cout << "A baby got sick!" << endl;
			cost = 500;
		}
		else
			cost = 250;
		if (cost <= balance) {
			balance -= cost;
			cout << "The cost to heal the Meerkat has been subtracted from you account." << endl;
			cout << "Your new balance is: " << balance << endl;
		}
		else {
			cout << "You dont have enough to fix this monkey!" << endl;
			cout << "Your animal has now died!" << endl;
			remove_animal(roll, nextRoll);
		}
	}
}

/*********************************************************************
 ** Function: remove animal
 ** Description: calls functions to remove animal
 *********************************************************************/
void Zoo::remove_animal(int &roll, int &nextRoll) {
	if (roll == 0) {
		remove_monkey(roll, nextRoll);
	}
	else if (roll == 1) {
		remove_otter(roll, nextRoll);
	}
	else if (roll == 2) {
		remove_meerkat(roll, nextRoll);
	}
}

/*********************************************************************
 ** Function: remove monkey
 ** Description: removes the dead animal from the array
 *********************************************************************/
void Zoo::remove_monkey(int &roll, int &nextRoll) {
	Animal *temp = new Monkey[total_monkeys]; //temp array

	for (int i = 0; i < total_monkeys; i++) {
		if (i != nextRoll) {
			temp[i] = animals[0][i];	//if it is not the sick animal store in temp array
		}
	}
	
	delete[] animals[0];
	total_monkeys -= 1;	//update total
	for (int i = 0; i < total_monkeys; i++) {
		animals[0][i] = temp[i];	//updates animal array
	}

	delete[] temp; //deletes memory
}

/*********************************************************************
 ** Function: remove otter
 ** Description: adds the according number of babies to the array with
 the age starting at 0 weeks
NOTE: same as monkey so no new comments
 *********************************************************************/
void Zoo::remove_otter(int &roll, int &nextRoll) {
	Animal *temp = new Otter[total_otters];

	for (int i = 0; i < total_otters; i++) {
		if (i != nextRoll) {
			temp[i] = animals[1][i];
		}
	}
	delete[] animals[1];
	total_otters -= 1;
	for (int i = 0; i < total_otters; i++) {
		animals[2][i] = temp[i];
	}

	delete[] temp; //delete temp
}

/*********************************************************************
 ** Function: remove meerkat
 ** Description: adds the according number of babies to the array with
 the age starting at 0 weeks
NOTE: same as monkey so no new comments
 *********************************************************************/
void Zoo::remove_meerkat(int &roll, int &nextRoll) {
	Animal *temp = new Meerkat[total_meerkats];

	for (int i = 0; i < total_meerkats; i++) {
		if (i != nextRoll) {
			temp[i] = animals[2][i];
		}
	}
	delete[] animals[2];
	total_meerkats -= 1;
	for (int i = 0; i < total_meerkats; i++) {
		animals[2][i] = temp[i];
	}

	delete[] temp; //delete temp
}

/*********************************************************************
 ** Function: get revenue
 ** Description: gets the revenue from all owned animals and add to balance
 *********************************************************************/
void Zoo::get_revenue() {
	int revenue = 0;
	cout << "It is time for your weekly revenue!" << endl;
	for (int i = 0; i < total_monkeys; i++) {
		if (animals[0][i].get_age() <= 5) {
			revenue += 3000;	//baby so twice as much
		}
		else {
			revenue += 1500;	//adult - adds to revenue 
		}
	}
	for (int i = 0; i < total_otters; i++) {
		if (animals[1][i].get_age() <= 5) {
			revenue += 500;		//also adds to revenue for each spot
		}
		else {
			revenue += 250;
		}
	}
	for (int i = 0; i < total_meerkats; i++) {
		if (animals[2][i].get_age() <= 5) {
			revenue += 50;
		}
		else {
			revenue += 25;
		}
	}
	balance += revenue; //updates balance adding revenue and display current amount
	cout << "You earned: " << revenue << endl;
	cout << "Your balance is now: " << balance << endl;
	cout << endl;
	cout << "Enter anything to continue: ";
	string in;
	cin >> in;
	//pauses for user input
}

/*********************************************************************
 ** Function: get food amount
 ** Description: gets amount of food for each animal
 *********************************************************************/
void Zoo::get_food_amount() {
	int weekly_cost = 0;
	for (int i = 0; i < total_monkeys; i++) {
		weekly_cost += foodCost * 4;	//adds to weekly cost with corresponding multiplier
	}
	for (int i = 0; i < total_otters; i++) {
		weekly_cost += foodCost * 2;
	}
	for (int i = 0; i < total_meerkats; i++) {
		weekly_cost += foodCost;
	}
	balance -= weekly_cost;				//updates balance
	cout << "You spent " << weekly_cost << " on food this week." << endl;
	cout << "Your balance is now " << balance << endl;
	check_balance();	//checks balance
	new_food_cost();	//gets new food cost for next time
}

/*********************************************************************
 ** Function: new food cost
 ** Description: gets new food cost for next week
 *********************************************************************/
void Zoo::new_food_cost() {
	srand(time(NULL));
	int random = 0;
	float rPercent;
	random = rand() % 51 + 75;	//random generate between 75 and 125
	rPercent = random * 0.01;	//turns into percentage
	foodCost = foodCost * rPercent;	//multiplies food cost by percent
	cout << "Starting next week your new base food cost will be $" << foodCost << endl;	//displays food cost for next week
	cout << endl;
	cout << "Enter anything to continue: ";
	string in;
	cin >> in;
	//waits for user input
}

/*********************************************************************
 ** Function: increment age
 ** Description: increments age of all animals by one week
 *********************************************************************/
void Zoo::increment_age() {
	int age = 0;
	cout << endl;
	cout << "This week has finished!" << endl;
	for (int i = 0; i < total_monkeys; i++) {
		age = animals[0][i].get_age();	//gets age
		age += 1;						//increments age by one week
		animals[0][i] = Monkey(age);	//stores the new age in the array
	}
	for (int i = 0; i < total_otters; i++) {
		age = animals[1][i].get_age();
		age += 1;
		animals[1][i] = Otter(age);
	}
	for (int i = 0; i < total_meerkats; i++) {
		age = animals[2][i].get_age();
		age += 1;
		animals[2][i] = Meerkat(age);
	}
}

/*********************************************************************
 ** Function: display animal
 ** Description: displays the current animals with updated week
 *********************************************************************/
void Zoo::display_animals() {
	int count;
	cout << "Here is an updated list of your animals and their ages(in weeks)!" << endl;
	for (int i = 0; i < total_monkeys; i++) {
		count = i + 1;
		if (i == 0)
			cout << "---Monkeys---" << endl;	//if at least one display title
		cout << count << ". " << animals[0][i].get_age() << endl;	//output age of animals
	}
	for (int i = 0; i < total_otters; i++) {
		count = i + 1;
		if (i == 0)
			cout << "---Sea Otters---" << endl;
		cout << count << ". " << animals[1][i].get_age() << endl;
	}
	for (int i = 0; i < total_meerkats; i++) {
		count = i + 1;
		if (i == 0)
			cout << "---Meerkats---" << endl;
		cout << count << ". " << animals[2][i].get_age() << endl;
	}
}
