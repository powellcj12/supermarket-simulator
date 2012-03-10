//
//  main.cpp
//  SupermarketSimulator
//
//  Created by Charles Powell on 2/26/12.
//

#include "Supermarket.h"
#include <iostream>

using namespace std;

int main ()
{  
    int config;
    
    cout << "Enter configuration (1-4): ";
    cin >> config;
    
    if (config >= 1 && config <= 4) {
        Supermarket * s = new Supermarket(config);
        
        string filename;
        cout << "Enter customer file name: ";
        cin >> filename;
        
        s->loadCustomers(filename);
        s->simulate();
        s->getResults(filename.append(".output"));
    }
    else
        cout << "Invalid configuration: " << config << endl;
    
    return 0;
}

