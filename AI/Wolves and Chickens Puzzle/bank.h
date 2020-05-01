#ifndef BANK_H
#define BANK_H


#include <iostream>


class Bank {
private:
    int chickens;
    int wolves;
    int boat;
    
public:
    Bank();
    void setChickens(int chickens);
    int getChickens();
    void setWolves(int wolves);
    int getWolves();
    void setBoat(int boat);
    int getBoat();
    

};
#endif