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
#include <algorithm>

using namespace std;

struct Register
{
    Customer* c;
    bool available;
    int items;
};

class Supermarket
{
public:
    const static int EXPRESS_ITEM_LIMIT = 5;

    Supermarket(int);
    ~Supermarket();
    void loadCustomers(string filename, char sorted);
    void simulate();
    void getResults(string);
    
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
    int totalCustWaitTime;
    int totalExpressCustWaitTime;
    int time;
    
    static bool customerComp(Customer* a, Customer* b);
    bool allQsEmpty();
    bool allRegsEmpty();
    bool placeCust(Customer*);
    void processRegs();
};

#endif
