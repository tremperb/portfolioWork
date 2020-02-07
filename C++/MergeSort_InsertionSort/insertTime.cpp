/* Name: Brayden Tremper 
 * Email: tremperb@oregonstate.edu
 * Course: CS325 - Analysis of Algorithms
 * Description: Insertion Time - Experimental runtime
 * Date: 1/14/2020
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono> //using chrono library to track runtime

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
    //cout << " - Sorted - " << endl;
    //print_vector(data); // print our updated vector
    //sendToFile(data);   //send to file
}

/*
 * This calls all other functions and track the runtime 
 * for each n printing them to the terminal
 * Citation: GeeksforGeeks, chronos library idea, https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
 */
int main() {
    int n = 10000; //start and increment each time for 10 times
    for(int i=1; i <= 10; i++) {
        vector <vector <int> > line = randomVector(n);  //get our 2d vector from previous function
 
    
        auto start = chrono::high_resolution_clock::now(); 

        insertsort (line); //call our sorting algorithm to sort our vector 
    
        auto end = chrono::high_resolution_clock::now();  //end clock
  
        //record duration
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
  
        time_taken *= 1e-9; //transform to seconds
  
        cout << i << ". For n = " << n << ": " << fixed << time_taken << " seconds" << endl;    
        n += 10000; //increment
    }


    return 0;
}