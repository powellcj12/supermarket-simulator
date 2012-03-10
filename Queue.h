//
//  queue.h
//  SupermarketSimulator
//
//  Created by Charles Powell on 2/27/12.
//

#ifndef SupermarketSimulator_Queue_h
#define SupermarketSimulator_Queue_h

#include "Customer.h"

struct node
{
    Customer* c;
    node* next;
};

class Queue
{
public:
    Queue();
    ~Queue();
    void enqueue(Customer*);
    Customer* dequeue();
    Customer* peek();
    int getCount();
    bool isEmpty();
    
private:
    node* head;
    node* tail;
    int count;
};

#endif
