/* Name: Brayden Tremper 
 * Email: tremperb@oregonstate.edu
 * Course: CS325 - Analysis of Algorithms
 * Description: Knapsack - recursion and dynamic time analysis 
 * Date: 2/05/2020
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

/*
 * Stores n variables between 1 & 20 in a vector for values
 */
vector <int> randomValue(int n) {
    vector <int> value;
      
    for(int i=0; i < n; i++) {
        value.push_back(rand() % 20+1);  //store in vector randomly generated
    }
    

    return value;
}

/*
 * Stores n variables between 1 & 20 in a vector for values
 */
vector <int> randomWeight(int n) {
    vector <int> weight;
      
    for(int i=0; i < n; i++) {
        weight.push_back(rand() % 20+1);  //store in vector randomly generated
    }
    

    return weight;
}

/*
 * This merely returns the max of two integer values
 */
int maxOf(int A, int B) {
    if(A >= B) {
        return A;
    }
    else {
        return B;
    }
}

/*
 * Here lies our recursive knapsack
 * Citation: Geeks for geeks, https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
 */
int recursiveKnapsack(vector <int> weight, vector <int> value, int maxWeight, int length) {
    if(length == 0 || maxWeight == 0) {
        return 0;   //base case so it doesn't go forever..
    }

    if(weight[length - 1] > maxWeight) {    //if our weight is greater than the max weight we can't do it so get the next
        return recursiveKnapsack(weight, value, maxWeight, length-1);
    }
    else {
        return maxOf(value[length-1] + recursiveKnapsack(weight, value, maxWeight-weight[length - 1], length - 1), recursiveKnapsack(weight, value, maxWeight, length - 1));
    }   //get the max of the values recursively going through table
}

/*
 * Here lies our dynamic knapsack
 * Citation: Geeks for geeks, https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
 */
int dynamicKnapsack(vector <int> weight, vector <int> value, int maxWeight, int length) {
    vector < vector <int> > knapsack(length+1, vector <int>(maxWeight+1, 0));
    
    
    for(int i = 1; i <= length; i++) {
        for(int j = 1; j <= maxWeight; j++) {
            if(weight[i-1] <= j) { //compare our weight to the current value of the max weight
                int val = value[i-1] + knapsack[i-1][j-weight[i-1]]; //update and subtract last weight from current
                knapsack[i][j] = maxOf(val, knapsack[i-1][j]);      //get max 
            }
            else {
                knapsack[i][j] = knapsack[i-1][j];  //get next
            }
        }

    }

    return knapsack[length][maxWeight]; //return our value
}

int getRecTime(vector <int> weight, vector <int> value, int n) {
    auto start = chrono::high_resolution_clock::now(); //start the clock

        int recVal = recursiveKnapsack(weight, value, 100, n);

    auto end = chrono::high_resolution_clock::now(); //end the clock
    //record duration, start - end, only for sorting algorithm
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9; //convert to seconds keeping decimal points for precision
    cout << " Rec Time: " << fixed << time_taken << " ";

    return recVal;
}

int getDynTime(vector <int> weight, vector <int> value, int n) {
    auto start = chrono::high_resolution_clock::now(); //start the clock

        int dynVal = dynamicKnapsack(weight, value, 100, n);

    auto end = chrono::high_resolution_clock::now(); //end the clock
    //record duration, start - end, only for sorting algorithm
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9; //convert to seconds keeping decimal points for precision
    cout << "| DP Time: " << fixed << time_taken << " | ";

    return dynVal;
}

/*
 * This calls all other functions and track the runtime 
 * for each n printing them to the terminal
 * Citation: GeeksforGeeks, chronos library idea, https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
 */
int main() {
    int n = 10; //start and increment each time for 10 times
    for(int i = 1; i <= 7; i++) {
        
        cout << "_______________________________________________";
        cout << "_______________________________________________"<< endl;
        vector <int> weight = randomWeight(n);
        vector <int> value = randomValue(n);
        cout << "| N = " << n << " | W = 200 |";

        int recVal = getRecTime(weight, value, n);
        int dynVal = getDynTime(weight, value, n);

        cout << "max Rec = " << recVal << " | max DP = " << dynVal << " |";
        cout << endl;
        n += 5; //next n
    }

    return 0;
}