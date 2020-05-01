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
 * This store the members of our current person and returns a vector containing them
 */
vector <int> storeMembers(int length, int w, int members, vector <int> weight, vector <int> value, vector < vector <int> > knapsack) {
    vector <int> memHolder;

    
    for(int i = length; 0 < i; i--) { //Go backwards through length
        if(members == 0) {  //base case, now we can break loop
            break;
        }
        else if(members != knapsack[i-1][w]) {  //only if there
            memHolder.push_back(i); //get our current member
            members -= value[i-1];  //now get the next one
            w -= weight[i-1];   //now get the next one
            //These basically do the opposite of our dynamic program to see the select values
        }
        
    }

    return memHolder;
}

/*
 * Here lies our dynamic knapsack
 * Citation: Geeks for geeks, https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
 */
int dynamicKnapsack(vector <int> weight, vector <int> value, int maxWeight, int length, vector <int> &storeMem) {
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

    storeMem = storeMembers(length, maxWeight, knapsack[length][maxWeight], weight, value, knapsack);
    //Store our members vector back through our function which updates in main since it is reference.

    return knapsack[length][maxWeight]; //return our value
}

/*
 * This is just a simple printing and sending algorithm
 * This prints our standard info and then just loops through our vector printing each
 * value for each mamily member until the family has been through. It then uses this same
 * approach to send it to the file, results.txt
 */
void printResults(int i, int maxValue, int familySize, vector < vector <int> > memberItems) {
    cout << endl;
    cout << "Test Case " << i << endl;
    cout << "Total Price " << maxValue << endl;
    cout << "Member Items: " << endl;
       
    for(int j=0; j < familySize; j++) {
        cout << j+1 << ": ";
        for(int k=memberItems[j].size(); k >0; k--) {
            cout << memberItems[j][k-1] << " ";
        }
        cout << endl;
    }
    cout << endl;

    ofstream wf;
    wf.open("results.txt", ios_base::app); //Note: appending since this runs every case
    wf << "Test Case " << i << endl;
    wf << "Total Price " << maxValue << endl;
    wf << "Member Items: " << endl;

    for(int j=0; j < familySize; j++) {
        wf << j+1 << ": ";
        for(int k=memberItems[j].size(); k >0; k--) {
            wf << memberItems[j][k-1] << " ";
        }
        wf << endl;
    }
    wf << endl;
    wf.close();
}


/*
 * Our main function though kinda long just reads in the items from the .txt file
 * then it finds the max of them using our knapsack function which was already 
 * written in the last program. Along with this though it gets our member items as well.
 */
int main() {
    ifstream rf; //to read file where rf = readfile
    
	rf.open("shopping.txt");    //open our file
    if(rf.good() != true) { 
		cout << "Error!" << endl;   //if unsuccessful, quit
        exit(0);
	}
    
    //create vectors to store our price and weight
    vector <int> price; 
    vector <int> weight;

    int T; //#test cases
    rf >> T;

    for(int i=1; i <= T; i++) {
        int numItems = 0; //# items
        int familySize = 0; //# of people in family
        int maxCarry = 0; //their max carry size
        int pHold;  //values to read in file to be pushed into our vector
        int wHold;
        rf >> numItems;
        for(int j=0; j < numItems; j++) { //do that for the number of items 
            rf >> pHold;
            rf >> wHold;
            price.push_back(pHold); //push those values in the vector
            weight.push_back(wHold);
        }
        rf >> familySize;

        int maxValue = 0;
        vector <vector <int> > memberItems(100);
        for(int j=0; j < familySize; j++) { //for each member of the family get their max
            rf >> maxCarry;
            maxValue += dynamicKnapsack(weight, price, maxCarry, numItems, memberItems[j]);
            //adding for total family so keep adding everybodys together
        }

        printResults(i, maxValue, familySize, memberItems);
        //clear our vectors so they are empty for the next test case
        price.clear();  
        weight.clear();
        
    }

    rf.close();

    return 0;
}