//
//  queue.cpp
//  SupermarketSimulator
//
//  Created by Charles Powell on 2/27/12.
//

#include "Queue.h"

Queue::Queue()
{
    head = NULL;
    tail = head;
}

Queue::~Queue()
{
    node* temp = head;
    
    while(head)
    {
        temp = temp -> next;
        delete head;
        head = temp;
    }
    
    tail = NULL;
}

void Queue::enqueue(Customer* c)
{
    node* temp = new node;
    temp -> c = c;
    temp -> next = NULL;
    
    if(head)
        tail -> next = temp;
    else
        head = temp;
    
    tail = temp;
    
    count++;
}

Customer* Queue::dequeue()
{
    Customer* temp = NULL;
    
    if(head)
    {
        temp = head -> c;
        head = head -> next;
        count--;
    }
    
    return temp;
}

Customer* Queue::peek()
{
    return head -> c;
}

int Queue::getCount()
{
    return count;
}

bool Queue::isEmpty()
{
    return (count == 0);
}