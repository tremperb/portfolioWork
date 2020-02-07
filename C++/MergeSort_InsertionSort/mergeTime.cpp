/* Name: Brayden Tremper 
 * Email: tremperb@oregonstate.edu
 * Course: CS325 - Analysis of Algorithms
 * Description: Merge time - experiemental runtime 
 * Date: 1/14/2020
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

/*
 * Stores n variables between 0 and 10000 in a vector
 */
vector <vector <int> > randomVector(int n) {
    vector <int> numbers;
    vector <vector <int > > line;   
    for(int i=0; i < n; i++) {
        numbers.push_back(rand() % 10001);  //store in vector randomly generated
    }
    line.push_back(numbers);    //puch back into 2d vector
    //don't really need 2d anymore but the code is already built for it and it shouldn't cause issues

    return line;
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
 * This calls all other functions and track the runtime 
 * for each n printing them to the terminal
 * Citation: GeeksforGeeks, chronos library idea, https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
 */
int main() {
    int n = 200000; //start and increment each time for 10 times
    for(int i = 1; i <= 10; i++) {
        vector <vector <int> > line = randomVector(n);  //get our 2d vector from previous function

        auto start = chrono::high_resolution_clock::now(); //start the clock

	    for(int i=0; i < line.size(); i++) {
            vector <int> temp = line[i];    //take our current line to be sorted
            mergeSort(temp, temp.size()-1, 0); //call sorting algorithm on that line
            line[i] = temp; //reassign that line
            //Now that line has been sorted so go to next
	    }
        
        auto end = chrono::high_resolution_clock::now(); //end the clock

        //record duration, start - end, only for sorting algorithm
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        
        time_taken *= 1e-9; //convert to seconds keeping decimal points for precision
  
        cout << i << ". For n = " << n << ": " << fixed << time_taken << " seconds" << endl;   
        n += 200000; //next n
    }

    return 0;
}