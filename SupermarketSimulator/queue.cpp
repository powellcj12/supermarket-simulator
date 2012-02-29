//
//  queue.cpp
//  SupermarketSimulator
//
//  Created by Charles Powell on 2/27/12.
//

#include "queue.h"
#include <iostream>

using namespace std;

template <typename T>
queue<T>::queue()
{
    head = NULL;
    tail = head;
}

template <typename T>
queue<T>::~queue()
{
    node<T>* temp = head;
    
    while(head)
    {
        temp = temp -> next;
        delete head;
        head = temp;
    }
    
    tail = NULL;
}

template <typename T>
void queue<T>::enqueue(const T item)
{
    node<T>* temp = new node<T>;
    temp -> data = item;
    temp -> next = NULL;
    
    if(head)
        tail -> next = temp;
    else
        head = temp;
    
    tail = temp;
    
    count++;
}

template <typename T>
T queue<T>::dequeue()
{
    T temp;//garbage
    
    if(head)
    {
        T temp = head -> data;
        node<T>* garbage = head;
        head = head -> next;
        delete garbage;
        count--;
    }
    
    return temp;//undefined behavior on empty queue
}

template <typename T>
T queue<T>::peek()
{
    return head -> data;
}

template <typename T>
int queue<T>::getCount()
{
    return count;
}

template <typename T>
bool queue<T>::isEmpty()
{
    return (count == 0);
}