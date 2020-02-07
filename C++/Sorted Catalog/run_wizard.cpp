/***********************************************************************
** Program Filename: catalog.cpp
** Author: Brayden Tremper
** Date: 4/14/2019
** Description: This program sorts a wizard spellbook. It requires the
**              user to login and decide how to sort it and where to display.
** Input: We input two text files, the users login credentials, how they
**        would like to sort it, and where to sort it with what name.
** Output: Outputs sorted values to either the screen or a file designated by the user.
*********************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include "catalog.h"

using namespace std;


/*********************************************************************
 * ** Function: main
 * ** Description: calls all function and takes in command line arguments
 * ** Parameters: command line arguments
 * ** Pre-Conditions: must be compiled w/ com.line and functions made
 * ** Post-Conditions: calls and prints all information
 * *********************************************************************/
int main( int argc, char ** argv) {
	/*Checks command line input*/
	char *fileOne = argv[1];
	char *fileTwo = argv[2];
	wizard* wizards;
	spellbook* spellbooks;
	spell* spells;

	ifstream rf;
	check_file( fileOne, fileTwo);
	rf.open( fileOne); /*opens file to read from use different name for other file*/
	int numWizards = get_num_wizards( fileOne);

	wizards = create_wizard_array( numWizards);
	fill_wizard( wizards, numWizards, rf);
	int person = match_user( wizards, numWizards);
	rf.close( );
	welcome( person, wizards);

	/*-End wizards-*/
	/*readsa and fills spell books*/
	rf.open( fileTwo);
	int numBooks = get_num_books( fileTwo);
	spellbooks = create_spellbooks( numBooks);
	get_spellbook_data( spellbooks, numBooks, rf);
	/*--Sorting--*/
	/*calls sorting and print function then dedletes memory*/
	string status = check_status( person, wizards);
	get_sort_type( spellbooks, numBooks, status);
	rf.close( );
	delete_info( &wizards, numWizards, &spellbooks, numBooks);

	return 0;
}


