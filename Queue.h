#pragma once

//
//  Breadth_First_Search.h
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright  2019 Daniel Vilajeti. All rights reserved.
//


class Queue
{
private:
    
    //Declaration of a node to be stored in queue
    struct node
    {
        //Every node contains a state ("move") and its corresponding parent state ("root_move")
        int move[3][3];
        int root_move[3][3];
        
        //pointer to next node
        node *next;
        
        //location of zero
        int row;
        int col;
    };
    
    //Pointer to the front of the queue
    node *front;
    
    //Pointer to the end of the queue
    node *rear;
    
    //Number of items in the queue
    int num_items;
    
public:
    
    Queue();
    
    ~Queue();
    
    void enqueue(int move[3][3], int **root_move, int row, int col);
    
    void dequeue(int **move, int **root_move, int *row, int *col);
    
    void dequeue();
    
    bool isEmpty();
    
    void clear();
    
    bool contains(int move[3][3]);
    
    bool compare(int move[3][3], int move2[3][3]);
    
    void copyArray(int **to, int from[3][3]);
    void copyArray(int to[3][3], int **from);
    
};
