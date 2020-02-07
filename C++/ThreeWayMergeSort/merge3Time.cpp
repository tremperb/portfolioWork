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
 * Merge 3, similar to regular mergesort but now split into thirds instead of halves
 */
void merge3(int left, int middleOne, int middleTwo, int right, vector <int> &data) {
   
    vector <int> temp = data;  //store our data in a temp array
    /*for(int i = 0; i < data.size(); i++) {
        temp.push_back(data[i]);            //**Had to take out as it caused an almost linear runtime
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
    int n = 25000;
    for(int i=1; i <= 10; i++) {
        vector <vector <int> > line = randomVector(n);  //get our 2d vector from previous function

        auto start = chrono::high_resolution_clock::now(); //start the clock

	    for(int i=0; i < line.size(); i++) {
            vector <int> temp = line[i];    //take our current line to be sorted
            mergesort3(0, temp.size(), temp); //call sorting algorithm on that line
     
            line[i] = temp; //reassign that line
        //Now that line has been sorted so go to next
	    }

        auto end = chrono::high_resolution_clock::now(); //end the clock

        //record duration, start - end, only for sorting algorithm
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
        
        time_taken *= 1e-9; //convert to seconds keeping decimal points for precision
  
        cout << i << ". For n = " << n << ": " << fixed << time_taken << " seconds" << endl;   
        n += 25000; //next n
        
    }
    
    return 0;
}