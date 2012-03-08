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

using namespace std;

struct Register
{
    Customer* c;
    int items;
    bool isExpress;
};

class Supermarket
{
public:
    Supermarket(int);
    ~Supermarket();
    void loadCustomers(string);
    void simulate();
    
private:
    Queue* custQ;
    Register* regs;
    Queue* doneQ;
    
    int numQs;
    int numRegs;
    int numExpressRegs;
    int numCusts;
    int numExpressCusts;
    int time;
    
    bool allQsEmpty();
};

#endif
