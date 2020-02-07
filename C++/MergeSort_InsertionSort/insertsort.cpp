/* Name: Brayden Tremper 
 * Email: tremperb@oregonstate.edu
 * Course: CS325 - Analysis of Algorithms
 * Description: Insertion Sort
 * Date: 1/14/2020
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

using namespace std;

/*
 * This function read the data in from the given data.txt file 
 * and then stores it in a 2d vector.
 */
vector <vector <int> > read_text() {
    ifstream rf;
    int line_length; //store length of line (first variable)
    int line_numbers; //store each number
    vector <vector <int > > line;   //2d vector to store individual lines
    vector<int> numbers;    //vector to store numbers
	rf.open("data.txt");    //open our file
    if(rf.good() != true) { 
		cout << "Error!" << endl;   //if unsuccessful, quit
        exit(0);
	}
    
    while(!rf.eof()) {  //while not at end of file
        rf >> line_length;  //read in the line length
        for(int i = 0; i < line_length; i++) {  //continue to get all numbers from that line
            rf >> line_numbers; //get the numbers not getting the first one
            numbers.push_back(line_numbers);    //push it to our vector
        }
        line.push_back(numbers);    //now push that vector to our 2d
        numbers.clear();    //clear the previous vector so its ready for next line
        
    }
   
    rf.close(); //close our file

    return line;
}

/*
 * This function prints the data to the terminal 
 * for easy visualization and debugging purposes.
 */
void print_vector (vector <vector <int> > line) {
    for(int i=0; i < line.size(); i++) {
        for(int j=0; j < line[i].size(); j++) {
            cout << line[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
 * This sends our sorted data to a new file called insert.txt
 */
void sendToFile(vector <vector <int> > data) {
    ofstream wf;
    wf.open("insert.txt");  //create a new file to be saved to

    for(int i=0; i < data.size(); i++) {
        for(int j=0; j < data[i].size(); j++) {
            wf << data[i][j] << " ";    //write our data with a space between
        }
        wf << endl; //once that set is finished create a new line
    }

    wf.close(); //close our file first and then we can access it
    cout << "Your sorted data has successfully been sent to: insert.txt" << endl;
}
/*
 * This sorts our data from smallest to biggest via insertion
 * sort algorithm. It works the way up the vector swapping values 
 * outwright until they are in their corresponding places.
 * ----
 * Citations: Used from a previous assignment in CS162, Sp2019
 * and adapted to fit with a 2d vector
 */
void insertsort (vector <vector <int> > data) {
    for(int i=0; i < data.size(); i++) {    //do this for each of our vectors
        for(int j=1; j < data[i].size(); j++) { //for all the values in current vector
            int currentVal = data[i][j];    //get our current value
            int previousVal = j - 1;        //get our index for previous val
            while(data[i][previousVal] >= currentVal && previousVal >= 0) { //do until the value is situated and within bounds
                data[i][previousVal + 1] = data[i][previousVal];    //set next value to previous i.e. moving it up
                previousVal--;              //decrement our previous value index
            }
            data[i][previousVal + 1] = currentVal;  //now set our value in corresponding place
        }
        
    }
    cout << " - Sorted - " << endl;
    print_vector(data); // print our updated vector
    sendToFile(data);   //send to file
}

/*
 * Our main function initializes some vlues and calls other functions
 */
int main() {
    vector <vector <int> > line = read_text();  //get our 2d vector from previous function

    cout << " - Unsorted - " << endl;
    print_vector(line); //print our unsorted data first for reference (not sent to file)

    insertsort (line); //call our sorting algorithm to sort our vector 

    return 0;
}