//
//  Supermarket.cpp
//  SupermarketSimulator
//
//  Created by Charles Powell on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Supermarket.h"

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
        regs[i].available = true;
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

void Supermarket::loadCustomers(string file, char sorted)
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
        
        if(c -> getNumItems() <= EXPRESS_ITEM_LIMIT)
            numExpressCusts++;
    }
    
    inFile.close();

    if(sorted == 'n')
        custList.sort(customerComp);
}

void Supermarket::simulate()
{
    //continue while there are still customers to process
    while(!allQsEmpty() || !custList.empty() || !allRegsEmpty())
    {
        list<Customer *>::iterator custItr = custList.begin();
        
        //go through all customers in waiting area
        while(custItr != custList.end() && (*custItr) -> getArrTime() <= time)
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

void Supermarket::getResults(string file)
{
    ofstream outFile;
    outFile.open(file.c_str(), ofstream::out);
    
    while(!doneQ.isEmpty())
    {
        Customer* c = doneQ.dequeue();
        outFile << c -> getName() << " " << c -> getNumItems() << " "
            << c -> getArrTime() << " " << c -> getWaitTime() << endl;
    }
    
    outFile.close();
    
    float avgWaitTime = (float)totalCustWaitTime/numCusts;
    float avgExpressWaitTime = (float)totalExpressCustWaitTime/numExpressCusts;
    
    cout << "Average wait time: " << avgWaitTime << "s\n";
    cout << "Average express wait time: " << avgExpressWaitTime << "s\n";
}

bool Supermarket::customerComp(Customer* a, Customer* b)
{
    return (a -> getArrTime() < b -> getArrTime());
}

bool Supermarket::allQsEmpty()
{    
    for(int i = 0; i < numQs; i++)
    {
        if(custQs[i].getCount() > 0)
            return false;
    }
    
    return true;
}

bool Supermarket::allRegsEmpty()
{
    for(int i = 0; i < numRegs; i++)
    {
        if(!regs[i].available)
            return false;
    }
    
    return true;
}

bool Supermarket::placeCust(Customer *c)
{
    int shortest = -1;
    
    if(numQs == 1) //bank configuration
        shortest = 0;
    else
    {
        for(int i = 0; i < numQs; i++)
        {
            //cout << custQs[i].getCount() << " " << custQs[shortest].getCount() << endl;
        
            if(shortest == -1 || 
               custQs[i].getCount() + (!regs[i].available) < custQs[shortest].getCount() + (!regs[shortest].available))
            {
                if(i < numExpressRegs) //only put here is express customer
                {
                    if(c -> getNumItems() <= EXPRESS_ITEM_LIMIT)
                        shortest = i;
                }
                else //choose first regular line
                    shortest = i;
            }
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
        int regLine = (numQs == 1) ? 0 : i;
        regs[i].items--;

        if(regs[i].items == 0 && !regs[i].available)
        {   //only add to done list if there's a customer here
            doneQ.enqueue(regs[i].c);
            regs[i].c = NULL;
            regs[i].available = true;
        }

        //put next customer in reg at the same time that someone is done
        //does not start checkout until next time increment, though
        if(regs[i].available && custQs[regLine].peek())
        {
            regs[i].c = custQs[regLine].dequeue();
            regs[i].available = false;
            regs[i].items = regs[i].c -> getNumItems();
            regs[i].c -> setWaitTime(time - regs[i].c -> getArrTime());
            totalCustWaitTime += regs[i].c -> getWaitTime();
            
            if(regs[i].c -> getNumItems() <= EXPRESS_ITEM_LIMIT)
                totalExpressCustWaitTime += regs[i].c -> getWaitTime();
        }
    }
}
