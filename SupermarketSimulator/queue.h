//
//  queue.h
//  SupermarketSimulator
//
//  Created by Charles Powell on 2/27/12.
//

#ifndef SupermarketSimulator_queue_h
#define SupermarketSimulator_queue_h

template <typename T>
struct node
{
    T data;
    node<T>* next;
};

template <typename T>
class queue
{
public:
    queue();
    ~queue();
    void enqueue(T item);
    T dequeue();
    int getCount();
    bool isEmpty();
    void print();
    
private:
    node<T>* head;
    node<T>* tail;
    int count;
};

#endif
