//
//  Breadth_First_Search.cpp
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright © 2019 Daniel Vilajeti. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "Queue.h"


using namespace std;

Queue :: Queue()
{
    front = nullptr;
    rear = nullptr;
    num_items = 0;
}

Queue::~Queue()
{
    clear();
}

void Queue::enqueue(int num)
{
    node *newNode = nullptr;
    
    newNode = new node;
    
    newNode->value = num;
    newNode->next = nullptr;
    
    if(isEmpty())
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    
    num_items++;
}

void Queue::dequeue(int &x)
{
    node *temp = nullptr;
    
    if(isEmpty())
    {
        cout<<"Queue is empty!\n";
    }
    else
    {
        x = front->value;
        temp = front;
        front = front->next;
        delete temp;
        
        num_items--;
        
    }
}

bool Queue::isEmpty()
{
    if (num_items > 0)
        return false;
    else
        return true;
}

void Queue::clear()
{
    int value;
    
    while(!isEmpty())
        dequeue(value);
}
