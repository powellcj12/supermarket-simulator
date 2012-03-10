//
//  Supermarket.cpp
//  SupermarketSimulator
//
//  Created by Charles Powell on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Supermarket.h"

const int EXPRESS_ITEM_LIMIT = 5;

Supermarket::Supermarket(int config)
{
    switch (config)
    {
        case 1:
            numQs = 1;
            numRegs = 1;
            numExpressRegs = 0;
            break;
        case 2:
            numQs = 4;
            numRegs = 4;
            numExpressRegs = 0;
            break;
        case 3:
            numQs = 4;
            numRegs = 4;
            numExpressRegs = 2;
            break;
        case 4:
            numQs = 1;
            numRegs = 4;
            numExpressRegs = 0;
            break;
    }
    
    waitArea = new Queue();
    custQs = new Queue[numQs];
    regs = new Register[numRegs];
    
    for(int i = 0; i < numRegs; i++)
    {
        regs[i].c = NULL;
        regs[i].items = 0;
        regs[i].isExpress = i < numExpressRegs;
    }
    
    doneQ = new Queue();
    numCusts = 0;
    numExpressCusts = 0;
    time = 0;
}

Supermarket::~Supermarket()
{
    delete waitArea;
    delete[] custQs;
    delete[] regs;
    delete doneQ;
}

void Supermarket::loadCustomers(string file)
{
    ifstream inFile;
    inFile.open(file.c_str(), ifstream::in);
    
    string name;
    int numItems, arrTime;
    
    while (inFile.good())
    {
        inFile >> name >> numItems >> arrTime;
        Customer* c = new Customer(name, numItems, arrTime);
        waitArea -> enqueue(c);
        numCusts++;
        
        if(c -> getNumItems() < EXPRESS_ITEM_LIMIT)
            numExpressCusts++;
    }
    
    inFile.close();
}

void Supermarket::simulate()
{
    while(!allQsEmpty())
    {
        time++;
    }
}

bool Supermarket::allQsEmpty()
{
    bool ans = true;
    
    for(int i = 0; i < numQs; i++)
        ans = ans && custQs[i].isEmpty();
    
    return ans;
}
