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

        char sorted;
        cout << "Is the file sorted by increassing arrival time (y or n)? ";
        cin >> sorted;
        
        s->loadCustomers(filename, sorted);
        s->simulate();
        s->getResults(filename.append(".out"));
    }
    else
        cout << "Invalid configuration: " << config << endl;
    
    return 0;
}

