//
//  Customer.h
//  SupermarketSimulator
//
//  Created by Charles Powell on 3/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SupermarketSimulator_Customer_h
#define SupermarketSimulator_Customer_h

#include <string>

class Customer
{
public:
    Customer();
    Customer(std::string custName, int num, int arr);
    int getArrTime();
    int getNumItems();
    std::string getName();
    void setWaitTime(int);
    int getWaitTime();
    
private:
    std::string name;
    int arrivalTime;
    int numItems;
    int waitTime;
};

#endif
