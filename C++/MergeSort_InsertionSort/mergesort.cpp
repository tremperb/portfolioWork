/* Name: Brayden Tremper 
 * Email: tremperb@oregonstate.edu
 * Course: CS325 - Analysis of Algorithms
 * Description: Merge sort 
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
 * This sends our sorted data to a new file called merge.txt
 */
void sendToFile(vector <vector <int> > data) {
    ofstream wf;
    wf.open("merge.txt");  //create a new file to be saved to

    for(int i=0; i < data.size(); i++) {
        for(int j=0; j < data[i].size(); j++) {
            wf << data[i][j] << " ";    //write our data with a space between
        }
        wf << endl; //once that set is finished create a new line
    }

    wf.close(); //close our file first and then we can access it
    cout << "Your sorted data has successfully been sent to: merge.txt" << endl;
}

/*
 * This function merges our halves of the vector sorting
 * them in increasing order. No output but the data is brought
 * in by reference allowing it to be adjusted.
 * Citation: CS162 Lab #9 Sp. 2019 & Textbook pg.34
 */
void merge(vector<int> &data, int rightSide, int leftSide, int middle) {

	int leftTemp = middle - leftSide + 1;	//middle - left
	int rightTemp = rightSide - middle;	//right side - middle

    vector<int> L;  //create vectors to hold each side
    vector<int> R;

	for (int i = 0; i < leftTemp; i++) {
		L.push_back(data[leftSide + i]);    //fill our vector with contents from original
	}
	for (int j = 0; j < rightTemp; j++) {
		R.push_back(data[middle + j + 1]);   //same thing but this is right side
	}

	//beginning of 1st, 2nd, and merged array
	int leftInitial = 0;    //initial values
    int rightInitial = 0;
    int mergeInitial = leftSide; //left side to move up vector

    while(leftInitial < leftTemp && rightInitial < rightTemp) { //while true
        if(L[leftInitial] < R[rightInitial]) {  //if left is less than right
            data[mergeInitial] = L[leftInitial];    //make our dataa hold that value
            leftInitial++;  //now increase to get our next left value from sub array
        }
        else {  //otherwise the right is smaller so make that the next one
            data[mergeInitial] = R[rightInitial];   //same this but with right subarray
            rightInitial++;
        }
        mergeInitial++;
    }
    //assigns the remaining to our original vector
    while(leftInitial < leftTemp) {
        data[mergeInitial] = L[leftInitial];
        leftInitial++;  //increase for each to get next subarray element
        mergeInitial++; //increase as new elements are added to whole vector
    }
    while(rightInitial < rightTemp) {
        data[mergeInitial] = R[rightInitial];
        rightInitial++; //same thing for right side
        mergeInitial++; //also grow total vector size
    }
}

/*
 * This function recursively splits our vector in halves
 * then proceed to sort them via our merge algoritmn
 * Citation: CS162 Lab #9 Sp. 2019 & Textbook pg.34
 */
void mergeSort(vector <int> &data, int rightSide, int leftSide) {
    if(leftSide < rightSide) {
        int middle = leftSide + (rightSide - leftSide) / 2; //get our middle point
        //start recursive calls on respective sides
        mergeSort(data, middle, leftSide); //now our right bound is the middle
        mergeSort(data, rightSide, middle+1); //now our left bound is the middle plus 1

        //Now call our sorting algorithm
        merge(data, rightSide, leftSide, middle);
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
        mergeSort(temp, temp.size()-1, 0); //call sorting algorithm on that line
        line[i] = temp; //reassign that line
        //Now that line has been sorted so go to next
	}

    cout << " - Sorted - " << endl;
    print_vector(line);
    sendToFile(line); //send our sorted data to text file
    return 0;
}