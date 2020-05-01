# Analysis of Algorithms Homework
 Homework Assignment 3

# knapsack.cpp

This program was created and compile with c++ and are called knapsack.cpp.
In order to compile this, connect to the oregon state flip server in your terminal.
With this navigate to the corresponding folder to compile these.
Use:

g++ knapsack.cpp -std=c++11
a.out

This will compile the algorithms for both the 
recursive approach and dynamic which will print the results to the terminal 
in a table format displaying the information for each.

# An example of my output can be seen below:
______________________________________________________________________________________________
| N = 10 | W = 200 | Rec Time: 0.000856 | DP Time: 0.000044 | max Rec = 90 | max DP = 90 |
______________________________________________________________________________________________
| N = 15 | W = 200 | Rec Time: 0.027268 | DP Time: 0.000064 | max Rec = 159 | max DP = 159 |
______________________________________________________________________________________________
| N = 20 | W = 200 | Rec Time: 0.554230 | DP Time: 0.000080 | max Rec = 163 | max DP = 163 |
______________________________________________________________________________________________
| N = 25 | W = 200 | Rec Time: 3.656472 | DP Time: 0.000102 | max Rec = 157 | max DP = 157 |
______________________________________________________________________________________________
| N = 30 | W = 200 | Rec Time: 75.469873 | DP Time: 0.000118 | max Rec = 223 | max DP = 223 |
______________________________________________________________________________________________
| N = 35 | W = 200 | Rec Time: 582.531010 | DP Time: 0.000128 | max Rec = 187 | max DP = 187 |
______________________________________________________________________________________________
| N = 40 | W = 200 | Rec Time: 961.359901 | DP Time: 0.000145 | max Rec = 186 | max DP = 186 |


# shopping.cpp
This program was created and compile with c++ and are called shopping.cpp.
In order to compile this, download the shopping.txt file and place it in the same directory
then connect to the oregon state flip server in your terminal.
With this navigate to the corresponding folder to compile these.

use this:
g++ shopping.cpp
a.out 

This will print the results information to the terminal as well as
send it to a file named "results.txt" where you can view the results of the program.

# An example output can be seen below:

Test Case 1
Total Price 0
Member Items:
1:
2: 


Test Case 2
Total Price 435
Member Items:
1: 3 4 5 6
2: 2 4 5
3: 3 4 6
4: 3 4 5


Test Case 3
Total Price 83
Member Items:
1: 3
2: 2 3
3: 1 2 3
4: 2 3 4
5: 1 2 3 4
6: 1 2 3 4 
7: 2 3 5
8: 1 2 3 5
9: 2 3 4 5
10: 1 2 3 4 5


Test Case 4
Total Price 646
Member Items:
1: 1
2: 1
3: 2
4: 1 2
5: 1 5 
6: 2 3
7: 7
8: 1 7
9: 10
10: 2 7
11: 1 2 7
12: 2 10
13: 2 3 7
14: 1 2 3 7
15: 7 9
16: 7 10
17: 1 7 10
18: 2 7 9
19: 2 7 10
20: 1 2 7 10
21: 2 3 7 9
22: 2 3 7 10
23: 1 2 3 7 10
24: 7 9 10
25: 2 6 7 10
26: 2 3 5 7 10
27: 2 7 9 10
28: 2 3 6 7 10
29: 1 2 3 6 7 10
30: 2 3 7 9 10

