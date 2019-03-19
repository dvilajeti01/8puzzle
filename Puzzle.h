//
//  Puzzle.h
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright © 2019 Daniel Vilajeti. All rights reserved.
//


#include "Queue.h"

#ifndef Puzzle_h
#define Puzzle_h


class Puzzle
{
private:
   
    
    int initial_state [3] [3];
    int goal_state [3] [3];
    
    Queue explored;
    Queue frontier;
    
    
    

public:
    
    Puzzle(string goal);
    
    ~Puzzle();
    
    void solve();
    
    bool breadth_first(int initial_state[][],Queue explored, Queue frontier);
    
    bool Goal_Test(int initial_state[][],int goal_state[][]);
    
    int [][] next_state(int current_state[][]);
    
   
};


#endif /* Puzzle_h */
