/* Name: Brayden Tremper 
 * Email: tremperb@oregonstate.edu
 * Course: CS325 - Analysis of Algorithms
 * Description: Merge sort 3
 * Citations: Framework of code used from previous assignment 
 * Date: 1/23/2020
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
 * This sends our sorted data to a new file called merge.txt
 */
void sendToFile(vector <vector <int> > data) {
    ofstream wf;
    wf.open("merge3.txt");  //create a new file to be saved to

    for(int i=0; i < data.size(); i++) {
        for(int j=0; j < data[i].size(); j++) {
            wf << data[i][j] << " ";    //write our data with a space between
        }
        wf << endl; //once that set is finished create a new line
    }

    wf.close(); //close our file first and then we can access it
    cout << "Your sorted data has successfully been sent to: merge3.txt" << endl;
}

/*
 * Merge 3, similar to regular mergesort but now split into thirds instead of halves
 */
void merge3(int left, int middleOne, int middleTwo, int right, vector <int> &data) {
   
    vector <int> temp = data;  //store our data in a temp array
   /* for(int i = 0; i < data.size(); i++) {
        temp.push_back(data[i]);
    }*/
    
    //Starting indexes for each third of array
    int leftStart = left;   //starts at far left
    int midStart = middleOne; //starts at first third
    int rightStart = middleTwo; // starts at second third
    int mergeStart = left;  

    while(leftStart < middleOne && midStart < middleTwo && rightStart < right) {    //has to satisfy all 3 case 
        if(temp[leftStart] < temp[midStart] && temp[leftStart] < temp[rightStart]) { //if left is less than middle but also have to m
            data[mergeStart] = temp[leftStart];                                      //make sure it is less than right as well
            leftStart++;    //store the data in increment the sizes of each
            mergeStart++;
        }
        else if(temp[midStart] < temp[rightStart]) { //if first case not satisfied check if middle is < right value
            data[mergeStart] = temp[midStart];
            midStart++;     //store and increment
            mergeStart++;
        }
        else {  //other wise right value is the smallest, store and increment
            data[mergeStart] = temp[rightStart];
            rightStart++;
            mergeStart++;
        }
    }
    /*
     * Since its split in thirds we need to check for 2 as well as one
     */

    while(leftStart < middleOne && midStart < middleTwo) { //Now has to satisfy only left and middle portions
        if(temp[leftStart] < temp[midStart]) {  //same idea as before checking for each case 
            data[mergeStart] = temp[leftStart]; //Due to it being the same i will not bother commenting***
            mergeStart++;
            leftStart++;
        }
        else {
            data[mergeStart] = temp[midStart];
            mergeStart++;
            midStart++;
        }
    }
    while(midStart < middleTwo && rightStart < right) { //check middle and right
        if(temp[midStart] < temp[rightStart]) {
            data[mergeStart] = temp[midStart];
            mergeStart++;
            midStart++;
        }
        else {
            data[mergeStart] = temp[rightStart];
            mergeStart++;
            rightStart++;
        }
    }
    while(leftStart < middleOne && rightStart < right) { //final case now have to check left and middle
        if(temp[leftStart] < temp[rightStart]) {
            data[mergeStart] = temp[leftStart];
            mergeStart++;
            leftStart++;
        }
        else {
            data[mergeStart] = temp[rightStart];
            mergeStart++;
            rightStart++;
        }
    }
    
    /*
     * Now second cases are done we can end like regular merge sort but need one more for the middle
     */
    while(leftStart < middleOne) { //check left
        data[mergeStart] = temp[leftStart];
        mergeStart++;
        leftStart++;
    }
    while(midStart < middleTwo) { //check middle
        data[mergeStart] = temp[midStart];
        mergeStart++;
        midStart++;
    }
    while(rightStart < right) { //check right
        data[mergeStart] = temp[rightStart];
        mergeStart++;
        rightStart++;
    }
}
/*
 * Merge sort 3, finds bounds and calls merge3 recursively
 * Citations: Last assignment code
 */
void mergesort3(int left, int right, vector <int> &data) {
    if((right-left) > 1) {
        int mid1 = left + (right-left)/3; //one third
        int mid2 = left + (2* ((right-left)/3))+1; //2 thirds
        
        //Split into thirds so we need to do 3 recursive calls
        
        mergesort3(left, mid1, data);  //first third
        mergesort3(mid1, mid2, data);  // Second third
        mergesort3(mid2, right, data); // Last third

        //call merge 3 
        merge3(left, mid1, mid2, right, data);
        
    }
}

/*
 * Our main function initializes some vlues and calls other functions
 */
int main() {
    vector <vector <int> > line = read_text();  //get our 2d vector from previous function

    cout << " - Unsorted - " << endl;
    print_vector(line); //print our unsorted data first for reference (not sent to file)

	for(int i=0; i < line.size(); i++) {
        vector <int> temp = line[i];    //take our current line to be sorted
        mergesort3(0, temp.size(), temp); //call sorting algorithm on that line
     
        line[i] = temp; //reassign that line
        //Now that line has been sorted so go to next
	}

    cout << " - Sorted - " << endl;
    print_vector(line);
    sendToFile(line); //send our sorted data to text file
    
    return 0;
}