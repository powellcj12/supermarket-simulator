//
//  Supermarket.h
//  SupermarketSimulator
//
//  Created by Charles Powell on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SupermarketSimulator_Supermarket_h
#define SupermarketSimulator_Supermarket_h

#include "Queue.h"
#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

struct Register
{
    Customer* c;
    int items;
};

class Supermarket
{
public:
    Supermarket(int);
    ~Supermarket();
    void loadCustomers(string);
    void simulate();
    
private:
    list<Customer *> custList;
    Queue* custQs;
    Register* regs;
    Queue doneQ;
    
    int numQs;
    int numRegs;
    int numExpressRegs;
    int numCusts;
    int numExpressCusts;
    int time;
    
    bool allQsEmpty();
    //try to place customer in shortest, appropriate queue
    bool placeCust(Customer*);
    void processRegs();
};

#endif
