//
//  Customer.cpp
//  SupermarketSimulator
//
//  Created by Charles Powell on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Customer.h"

Customer::Customer()
{
    name = "";
    arrivalTime = 0;
    numItems = 0;
}
 
Customer::Customer(std::string custName, int num, int arr)
{
    name = custName;
    arrivalTime = arr;
    numItems = num;
}

int Customer::getArrTime()
{
    return arrivalTime;
}

int Customer::getNumItems()
{
    return numItems;
}

std::string Customer::getName()
{
    return name;
}

void Customer::setWaitTime(int wait)
{
    waitTime = wait + numItems;
}

int Customer::getWaitTime()
{
    return waitTime;
}