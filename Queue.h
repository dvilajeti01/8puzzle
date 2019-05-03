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
        
        int parent_cost;
        
        //f(n) =  g(h) + h(n) == path cost + manhattan distance
        int cost;
    };
    
    //Pointer to the front of the queue
    node *front;
    
    //Pointer to the end of the queue
    node *rear;
    
    //Number of items in the queue
    int num_items;
    
public:
    
    //Constructor
    Queue();
    
    //Destructor
    ~Queue();
    
    //Appends node to the queue
    void enqueue(int move[3][3], int **root_move, int row, int col);
    
    void priority_enqueue(int move[3][3], int ** root_move, int row, int col, int cost, int parent_cost);
    
    //Removes the first value in the Queue and updates the values(passed by reference) of the current state, root state and location of the empty space
    int dequeue(int **move, int **root_move, int *row, int *col);
    
    //Removes the first value of the queue but does not update any values
    void dequeue();
    
    //Tests if the Queue is empty(true) or not empty(false)
    bool isEmpty();
    
    //Empties the contents of the Queue
    void clear();
    
    //Looks through Queue to check for existence of given 2D Array
    bool contains(int move[3][3]);
    
    //Compares two given 2D Arrays
    bool compare(int move[3][3], int move2[3][3]);
    
    //Copies the values of the "from" array to the "to" Array
    void copyArray(int **to, int from[3][3]);
    void copyArray(int to[3][3], int **from);
    
    void updateNode(int state[3][3],int **root_state, int cost, int cumulative_cost);
    
};
