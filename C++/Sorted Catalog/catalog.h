/*Function prototypes*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>

using namespace std;

/*Creates structs for each part*/
struct wizard {
	string name;
	int id;
	string password;
	string position_title;
	float beard_length;
};

struct spellbook {
	string title;
	string author;
	int num_pages;
	int edition;
	int num_spells;
	float avg_success_rate;
	struct spell *s;
};

struct spell {
	string name;
	float success_rate;
	string effect;
};

void check_file( char *, char *);
int get_num_wizards( char *);
int get_num_books( char *);
wizard* create_wizard_array( int );
spellbook* create_spellbooks( int );
spell* create_spells( int );
void fill_wizard( wizard*, int , ifstream &);
void get_spellbook_data( spellbook* , int , ifstream &);
void get_spell_data( spell* , int , ifstream &);
void sort_pages( spellbook* , int );
void print_standard_effect( spellbook* , int );
void print_advanced_effect( spellbook* , int );
void sort_success( spellbook* , int n);
void output_sorted_success( spellbook* , int , string);
void output_sorted_pages( spellbook* , int , string);
int get_username(  );
int match_user( wizard* , int );
void welcome( int , wizard* );
string check_status( int , wizard* );
void add_one_char( char** , char);
char* get_input( );
void output_option( );
void get_sort_type( spellbook* , int , string );
void delete_info(  wizard** , int , spellbook** , int );

