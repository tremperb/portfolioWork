/*Functions*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include "catalog.h"

using namespace std;

/*********************************************************************
** Function: check_file
** Description: Checks to make sure files exist
** Parameters: fileone and filetwo both inputted from command line
** Pre-Conditions: user runs files through command line. Files in directory
** Post-Conditions: Post functions read from file.
*********************************************************************/
void check_file(char *fileOne, char *fileTwo) {
	ifstream rf;
	rf.open(fileOne);
	//Checks to see if file exists and if not true function exits
	//both files must exist
	if(rf.good() != true) {
		cout << "Error!\n" << fileOne << " does not exist!" << endl;
		exit (0);
	}
	rf.close();
	rf.open(fileTwo);
	if(rf.good() != true) {
		cout << "Error!\n" << fileTwo << " does not exist" << endl;
		exit(0);
	}
	rf.close();
}

/*********************************************************************
** Function: get_num_wizards
** Description: Gets the number of wizards
** Parameters: fileone containing wizards
** Pre-Conditions: fileone must be present
** Post-Conditions: used to create array of wizards
*********************************************************************/
int get_num_wizards(char *fileOne) {
	int numWizards;
	ifstream rf;

    //reads in number of wizards from text file
	rf.open(fileOne);
	rf >> numWizards;
	rf.close(); // closes

	return numWizards;
}

/*********************************************************************
** Function: get_num_books
** Description: gets number of books
** Parameters: filetwo containg books
** Pre-Conditions: filetwo must be present
** Post-Conditions: used to create array of books
*********************************************************************/
int get_num_books(char *fileTwo) {
	int numBooks;
	ifstream rf;

	//reads in number of books from text file
	rf.open(fileTwo);
	rf >> numBooks;
	rf.close(); // closes

	return numBooks;
}

/*********************************************************************
** Function: create_wizard_array
** Description: creates array on heap of wizards w/ struct
** Parameters: number of wizards and wizard struct
** Pre-Conditions: wizard struct and number of wizards are initialized
** Post-Conditions: array used to store values
*********************************************************************/
wizard* create_wizard_array(int numWizards) {
	wizard* wizards;

	wizards = new wizard[numWizards]; //creates on heap size of number of wizards

	return wizards;

}

/*********************************************************************
** Function: create_spellbooks
** Description: creates array on heap of spellbooks w/ struct
** Parameters: number of books and spellbook struct
** Pre-Conditions: inputs are initialized
** Post-Conditions: array used to store contents
*********************************************************************/
spellbook* create_spellbooks(int numBooks) {
	spellbook* spellbooks;

	spellbooks = new spellbook[numBooks]; // creates array on heap size of #books

	return spellbooks;
}

/*********************************************************************
** Function: create_spells
** Description: creates and array of spells on heap
** Parameters: the number of spells and struct
** Pre-Conditions: struct and # must be initialized. num_spells from spellbooks
** Post-Conditions: used to store spells
*********************************************************************/
spell* create_spells(int num_spells) {

	spell* spells = new spell[num_spells]; //creates array on heap size of spells

	return spells;
}

/*********************************************************************
** Function: fill_wizard
** Description: reads in values and fills array
** Parameters: wizard array, num of wizards and the file
** Pre-Conditions: values and text must be initialized
** Post-Conditions: will be sorted accordingly
*********************************************************************/
void fill_wizard(wizard* wizards, int numWizards, ifstream &rf) {
	string dummyLine;

	getline(rf, dummyLine);
	for(int i=0; i < numWizards; i++) {
        //reads input from file and store in according values of struct
		rf >> wizards[i].name;
		rf >> wizards[i].id;
		rf >> wizards[i].password;
		rf >> wizards[i].position_title;
		rf >> wizards[i].beard_length;
	}
}

/*********************************************************************
** Function: get_spellbook_data
** Description: reads in and fills spellbook w/ "values"
** Parameters: spellbook struct, number of books, and the file
** Pre-Conditions: All must be initialezed as well as array of spells
** Post-Conditions: will be used for sorting data in this and spells
*********************************************************************/
void get_spellbook_data(spellbook* spellbooks, int numBooks, ifstream &rf) {
	string dummyLine;
	float avg_success=0;

	getline(rf, dummyLine);

	for(int i=0; i < numBooks; i++) {
		avg_success = 0;
		//reads in info and stores in values from struct
		rf >> spellbooks[i].title;
		rf >> spellbooks[i].author;
		rf >> spellbooks[i].num_pages;
		rf >> spellbooks[i].edition;
		rf >> spellbooks[i].num_spells;
		spellbooks[i].s = create_spells(spellbooks[i].num_spells); //calls function to create spells
		get_spell_data(spellbooks[i].s, spellbooks[i].num_spells, rf); //calls again allowing for s to be used
		for(int j=0; j < spellbooks[i].num_spells; j++){
			avg_success += spellbooks[i].s[j].success_rate; //gets average success for each book
		}
		spellbooks[i].avg_success_rate = avg_success / spellbooks[i].num_spells; // calculates it
	}
}

/*********************************************************************
** Function: get_spell_data
** Description: gets data for spells
** Parameters: struct, number of spells, file
** Pre-Conditions: all mmust be initialized and must be w/ values from
**                 previous function
** Post-Conditions: fills array to be sorted
*********************************************************************/
void get_spell_data(spell* spells, int num_spells, ifstream &rf) {
	string dummyLine;

	getline(rf, dummyLine);
	for(int i=0; i < num_spells; i++) {
        //Reads in from file
		rf >> spells[i].name;
		rf >> spells[i].success_rate;
		rf >> spells[i].effect;
	}
}

/*********************************************************************
** Function: sort_pages
** Description: sorts pages of books
** Parameters: struct, and num of books
** Pre-Conditions: all must be initialized
** Post-Conditions: will be sented and printed/sent to file
*********************************************************************/
void sort_pages(spellbook* spellbooks, int numBooks) {
	for(int i=0; i < numBooks; i++) {
		for(int j=0; j < numBooks-i; j++) {
			if(spellbooks[j].num_pages < spellbooks[j+1].num_pages){
				spellbook temp = spellbooks[j+1];
				spellbooks[j+1] = spellbooks[j];
				spellbooks[j] = temp;
				//bubble sort which orders pages
			}
		}
	}
}

/*********************************************************************
** Function: print_standard_effect
** Description: prints standard elements (effects) availale to all users
** Parameters: spellbooks, spells, and the amount of each
** Pre-Conditions: All must be initialized
** Post-Conditions: will be printed/sent to file
*********************************************************************/
void print_standard_effect(spellbook* spellbooks, int numBooks) {
	for(int i=0; i < numBooks; i++) {
		for(int j=0; j < spellbooks[i].num_spells; j++) {
			if(spellbooks[i].s[j].effect.compare("bubble") == 0) {
                //prints all occurences of desired word. Same for each word
                //more for loops to limit print statements
				cout << spellbooks[i].s[j].effect << " " << spellbooks[i].s[j].name << endl;
			}
		}
	}
	for( int i=0; i < numBooks; i++) {
		for( int j=0; j < spellbooks[i].num_spells; j++) {
			if( spellbooks[i].s[j].effect.compare( "memory_loss") == 0) {
				cout << spellbooks[i].s[j].effect << " " << spellbooks[i].s[j].name << endl;
			}
		}
	}
	for( int i=0; i < numBooks; i++) {
		for( int j=0; j < spellbooks[i].num_spells; j++) {
			if( spellbooks[i].s[j].effect.compare( "fire") == 0) {
				cout << spellbooks[i].s[j].effect << " " << spellbooks[i].s[j].name << endl;
			}
		}
	}
}

/*********************************************************************
** Function: print_advance_effect
** Description: prints effect of advanced spells
** Parameters: spell book, spells, and amount of each
** Pre-Conditions: user must not be a student and values initialized
** Post-Conditions: will be printed/sent to file
*********************************************************************/
void print_advanced_effect(spellbook* spellbooks, int numBooks) {
	for( int i=0; i < numBooks; i++) {
		for( int j=0; j < spellbooks[i].num_spells; j++) {
			if( spellbooks[i].s[j].effect.compare( "poison") == 0) {
                //checks to see if matches high level spell
				cout << spellbooks[i].s[j].effect << " " << spellbooks[i].s[j].name << endl;
			}
		}
	}
	for( int i=0; i < numBooks; i++) {
		for( int j=0; j < spellbooks[i].num_spells; j++) {
			if( spellbooks[i].s[j].effect.compare( "death") == 0) {
				cout << spellbooks[i].s[j].effect << " " << spellbooks[i].s[j].name << endl;
			}
		}
	}
}

/*********************************************************************
** Function: sort_success
** Description: sorts books by avg success rate
** Parameters: spells book and amount
** Pre-Conditions: all must be initialized. function called
** Post-Conditions: will be prited if desired by user
*********************************************************************/
void sort_success(spellbook* spellbooks, int numBooks) {
	for(int i=0; i < numBooks; i++) {
		for(int j=0; j < numBooks-i; j++) {
			if(spellbooks[j].avg_success_rate < spellbooks[j+1].avg_success_rate){
				spellbook temp = spellbooks[j+1];
				spellbooks[j+1] = spellbooks[j];
				spellbooks[j] = temp;
			}
		}
	}
}

/*********************************************************************
** Function: output_sorted_success
** Description: prints sorted values and hides some if student
** Parameters: the books and amount and status of user
** Pre-Conditions: all must be initialized
** Post-Conditions: will be printed if desired
*********************************************************************/
void output_sorted_success(spellbook* spellbooks, int numBooks, string status) {
	cout << "SORTED BY AVERAGE SUCCESS: " << endl;
	if(status == "low") { //if user is not high enough status
		for(int i=0; i < numBooks; i++) {
			for(int j=0; j < spellbooks[i].num_spells; j++) {
				if((spellbooks[i].s[j].effect.compare("death") == 0) || (spellbooks[i].s[j].effect.compare("poison") == 0)) {
					spellbooks[i].title = "hide"; //if it contains one of types replace title with hide
				}
			}
		}
	}
	for(int i=0; i < numBooks; i++){
		if(spellbooks[i].title != "hide") //print only if the title isnt hide
			cout << spellbooks[i].title << " " << spellbooks[i].avg_success_rate << endl;
	}
}

/*********************************************************************
** Function: output_sorted_pages
** Description: prints pages which have been sorted
** Parameters: spellbooks, amount and status of user
** Pre-Conditions: all must be initialized
** Post-Conditions: will print to screen or file
*********************************************************************/
void output_sorted_pages(spellbook* spellbooks, int numBooks, string status) {
	cout << "SORTED SPELLBOOKS: " << endl;
	if(status == "low") {//if user is not high enough status
		for(int i=0; i < numBooks; i++) {
			for(int j=0; j < spellbooks[i].num_spells; j++) {
				if((spellbooks[i].s[j].effect.compare("death") == 0) || (spellbooks[i].s[j].effect.compare("poison") == 0)) {
					spellbooks[i].title = "hide";//if it contains one of types replace title with hide
				}
			}
		}
	}
	for(int i=numBooks-1; i >= 0; i--) {
		if(spellbooks[i].title != "hide") //print only if the title isnt hide
			cout<< spellbooks[i].title << " " << spellbooks[i].num_pages << endl;
	}
}

/*********************************************************************
** Function: get_username
** Description: get id from user
** Parameters: na
** Pre-Conditions: must have proper command line arguments
** Post-Conditions: will be compared to see if valid
*********************************************************************/
int get_username( ) {
	string s;
	int error = 0;
	do{
		error = 0;
		cout << "Please enter your id: ";
		getline(cin, s);
		for(int i=0; i < s.size(); i++) {
			if(!(s.at(i) >= '0' && s.at(i) <= '9')) {
                //checks to be sure every letter is an integer
				cout << "ERROR! Username must be integers" << endl;
				error = 1;
			}
		}
	}while(error == 1);
	int x = atoi(s.c_str()); //convert string to integer

	return x;
}

/*********************************************************************
** Function: match_user
** Description: matches user id and password to see if valid. User gets
**              3 attempts before exiting
** Parameters: wizards and amount
** Pre-Conditions: all must be initialized
** Post-Conditions: will be used to print user info
*********************************************************************/
int match_user(wizard* wizards, int numWizards) {
	int error = 0;
	string password;
	int count = 0;
	int person;
	do{
		int username = get_username();
		cout << "Please enter your password: ";
		getline(cin, password);
		for(int i=0; i < numWizards; i++) {
			if((password.compare(wizards[i].password) == 0) && (username == wizards[i].id)) {
				error = 0; //checks to see if inputs are valid from text file
				person = i;
				break;
			}
			else{
				error = 1;
				if(count == 2){
					cout << "Too many failed attempts! This program will now end!" << endl;
					exit(0); // if too many failed attempts quit
				}
			}
		}
		if(error == 1) {
			cout << "Incorrect username or password!" << endl;
		}
		count++;
	}while(error == 1);

	return person;
}

/*********************************************************************
** Function: welcome
** Description: prints user info
** Parameters: the user, and wizards array
** Pre-Conditions: all must be initialized
** Post-Conditions: printed to screen
*********************************************************************/
void welcome(int person, wizard* wizards) {
	cout << "Welcome: " << wizards[person].name << endl;
	cout << "ID: " << wizards[person].id << endl;
	cout << "Status: " << wizards[person].position_title << endl;
	cout << "Beard Length: " << wizards[person].beard_length << endl;
}

/*********************************************************************
** Function: check_status
** Description: checks status of user
** Parameters: the wizard and array of wizards
** Pre-Conditions: all must be initialized
** Post-Conditions: will be used to determine what spells he/she can see
*********************************************************************/
string check_status(int person, wizard* wizards) {
	string status;
	if(wizards[person].position_title.compare("Student") == 0)
		status = "low"; // if student they have low status
	else
		status = "high";

	return status;
}

/*********************************************************************
** Function: add_one_char
** Description: adds character to input allowing for multiple char
** Parameters: input of characters
** Pre-Conditions: all must be initialized
** Post-Conditions: deletes memory from temporary variable
*********************************************************************/
void add_one_char( char** str, char c) {
	char* temp = new char[strlen( *str) + 2];
	for (int i = 0; i < strlen( *str); i ++) {
		temp[i] = ( *str)[i];
	}
	temp[strlen( *str)] = c;
	temp[strlen( *str) + 1] = '\0';
	delete [] ( *str);
	(*str) = new char[strlen( temp) + 1];
	strcpy( ( *str), temp);
	delete [] temp;
}

/*********************************************************************
** Function: get_input
** Description: gets input for file
** Parameters: na
** Pre-Conditions: must be called
** Post-Conditions: name will be recorded and sent to be made and filled
*********************************************************************/
char* get_input( ) {
	char* str = new char[1];
	*str = '\0';
	cout << "Please enter a file name to send to: ";
	cin >> str;
	while ( cin.peek() != '\n') {
		add_one_char(&str, cin.get()); // calls functions to add char
	}
	cin.ignore( );
	cin.clear( );

	return str;
}

/*********************************************************************
** Function: output_option
** Description: gets desired output option
** Parameters: na
** Pre-Conditions: must be called
** Post-Conditions: prints to file or write to screen
*********************************************************************/
void output_option() {
	string output;
	char* outFile;
	int error;
	do{
		error = 0;
		cout << "How would you like this information to be displayed?" << endl;
		cout << "Print to screen (Enter 1): " << endl;
		cout << "Print to file (Enter 2): " << endl;
		cin >> output;
		if(output == "2") {
			outFile = get_input();
			ifstream of;
			of.open(outFile);
			if(of.good() != true) {
				cout << "Information has been sent to: " << outFile << endl;
				freopen(outFile, "w", stdout); //writes file
				//reads cout statements after this point and sends all to file
			}
			else {
				cout << "Appended information to file." << endl;
				freopen(outFile, "a", stdout); //sends to already created file
			}
			of.close();
			delete [] outFile; //deletes memory
		}
		else if(output != "1" && output != "2") {
			cout << "ERROR!" << endl;
			error = 1;
		}
	}while(error == 1);
}

/*********************************************************************
** Function: get_sort_type
** Description: gets desired way to sort and prints all outputs
** Parameters: spellbooks, number of books, and user status
** Pre-Conditions: all must be initiliazed
** Post-Conditions: prints to screen or file
*********************************************************************/
void get_sort_type(spellbook* spellbooks, int numBooks, string status) {
	string type;
	int error;
	do{
		error = 0;
		cout << "How would you like to sort this book?"<<"\nSort by number of pages (Enter 1): " << endl;
		cout << "Group spells by their effect (Enter 2): " << "\nSort by average success rate: (Enter 3): " << endl;
		cout << "Quit (Enter 4): " << endl;
		cin >> type;
		if(type == "1"){
			output_option(); // calls output option and sorts
			sort_pages(spellbooks, numBooks);
			output_sorted_pages(spellbooks, numBooks, status);
			fclose(stdout); //stopps reading to file if chosen
		}
		else if(type == "2"){
			output_option();
			if(status == "low") {
				print_standard_effect(spellbooks, numBooks);
			}
			else {
				print_standard_effect(spellbooks, numBooks);
				print_advanced_effect(spellbooks, numBooks);
			}
			fclose(stdout);
		}
		else if(type == "3"){
			output_option();
			sort_success(spellbooks, numBooks);
			output_sorted_success(spellbooks, numBooks, status);
			fclose(stdout);
		}
		else if(type == "4"){
			exit(0); //exits program
		}
		else{
			cout << "Not valid!" << endl;
			error = 1;
		}
	} while(error == 1);
}

/*********************************************************************
** Function: delete_info
** Description: deletes heap meory
** Parameters: wizards and spellbooks and amount of each
** Pre-Conditions: all must be initialized
** Post-Conditions: deletes memory not to be used after
*********************************************************************/
void delete_info( wizard** wizards, int numWizards, spellbook ** spellbooks, int numBooks) {
	delete [] *wizards;
	*wizards = NULL;

	for(int i=0; i < numBooks; i++) {
		delete [] (*spellbooks)[i].s; //deletes for each spot in array
	}

	delete [] (*spellbooks);
	*spellbooks = NULL;
}

