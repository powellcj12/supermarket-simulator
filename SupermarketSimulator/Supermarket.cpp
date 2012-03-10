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
    
    custQs = new Queue[numQs];
    regs = new Register[numRegs];
    
    for(int i = 0; i < numRegs; i++)
    {
        regs[i].c = NULL;
        regs[i].items = 0;
    }
    
    numCusts = 0;
    numExpressCusts = 0;
    totalCustWaitTime = 0;
    totalExpressCustWaitTime = 0;
    time = 0;
}

Supermarket::~Supermarket()
{
    delete[] custQs;
    delete[] regs;
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
        custList.push_back(c);
        numCusts++;
        
        if(c -> getNumItems() < EXPRESS_ITEM_LIMIT)
            numExpressCusts++;
    }
    
    inFile.close();
}

void Supermarket::simulate()
{
    //continue while there are still customers to process
    while(!allQsEmpty() && !custList.empty())
    {
        list<Customer *>::iterator custItr = custList.begin();
        
        //go through all customers in waiting area
        while((*custItr) -> getArrTime() >= time && custItr != custList.end())
        {
            if(placeCust(*custItr))
                custItr = custList.erase(custItr); //this effectively iterates
            else
                custItr++;
        }
        
        processRegs();
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

bool Supermarket::placeCust(Customer *c)
{
    int shortest = -1;
    
    for(int i = 0; i < numQs; i++)
    {
        //if this line is shorter
        if(shortest == -1 || custQs[i].getCount() < custQs[shortest].getCount())
        {
            if(i < numExpressRegs) //if express line, check if customer is express
            {
                if(c -> getNumItems() <= EXPRESS_ITEM_LIMIT)
                    shortest = i;
            }
            else //if not an express line, we're all good
                shortest = i;
        }
    }
    
    if(shortest != -1)
    {
        custQs[shortest].enqueue(c);
        return true;
    }
    
    return false;
}

void Supermarket::processRegs()
{
    for(int i = 0; i < numRegs; i++)
    {
        if(regs[i].items == 0)
        {
            regs[i].c = custQs -> dequeue();
            regs[i].items = regs[i].c -> getNumItems();
            regs[i].c -> setWaitTime(time - regs[i].c -> getArrTime());
            
            totalCustWaitTime += regs[i].c -> getWaitTime();
            
            if(regs[i].c -> getNumItems() <= EXPRESS_ITEM_LIMIT)
                totalExpressCustWaitTime += regs[i].c -> getWaitTime();
        }
        
        regs[i].items--;
        
        if(regs[i].items == 0)
            doneQ.enqueue(regs[i].c);
    }
}
