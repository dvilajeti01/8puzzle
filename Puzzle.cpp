//
//  Puzzle.cpp
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/4/19.
//  Copyright 2019 Daniel Vilajeti. All rights reserved.
//

#include <stdio.h>
#include "Puzzle.h"
#include <iostream>
#include <unordered_map>
#include <time.h>
using namespace std;

//Deffault constructor which produces a randomly generated initial state
Puzzle::Puzzle()
{
    shuffle(initial_state);
    
}

//Construct a puzzle with user specified initial state
Puzzle::Puzzle(int state[3][3])
{
    //Copies the user specified state to the initial state
    memcpy(initial_state, state, sizeof(initial_state));
    
    //locates where the "0" or empty square lies
    findZero(initial_state, &this->row, &this->col);
    
}

Puzzle::~Puzzle()
{
    //Deletes all dynamically allocated memory
    for (int i = 0; i < 3; i++)
    {
        delete[] current_state[i];
    }
    
    delete[] current_state;
    
    for (int i = 0; i < 3; i++)
    {
        delete[] root_state[i];
    }
    
    delete[] root_state;
    
    explored.clear();
}

void Puzzle::getGoalState(int ** state)
{
    copyArray(state, goal_state);
}

void Puzzle::getInitialState(int ** state)
{
    copyArray(state, initial_state);
}

void Puzzle::solve(string search_algo)
{
    if (search_algo == "BFS")
    {
        if (!breadth_first(this->initial_state))
            cout << "NOT SOLVE-ABLE";
    }
    else if (search_algo == "A_Star")
    {
        if (!A_star(this->initial_state))
            cout << "NOT SOLVE-ABLE";
    }
    else
        cout << "INVALID SEARCH ALGO\n";
}

bool Puzzle::breadth_first(int initial_state[3][3])
{
    if (Goal_Test(initial_state))
    {
        printState(initial_state);
        return true;
    }
    
    frontier.enqueue(initial_state, NULL, this->row, this->col);
    
    while (!frontier.isEmpty())
    {
        current_state = new int *[3];
        for (int i = 0; i < 3; i++)
            current_state[i] = new int[3];
        
        root_state = new int *[3];
        for (int i = 0; i < 3; i++)
            root_state[i] = new int[3];
        
        frontier.dequeue(current_state, root_state, &this->row, &this->col);
        explored[current_state] = root_state;
        
        
        if (next_state(this->current_state, this->row, this->col))
        {
            return true;
        }
        
    }
    
    return false;
}

bool Puzzle::A_star(int initial_state[3][3])
{
    int cumulativeCost;
    
    frontier.priority_enqueue(initial_state, NULL, this->row, this->col, Heuristic_func(initial_state),0);
    
    while (!frontier.isEmpty())
    {
        current_state = new int *[3];
        for (int i = 0; i < 3; i++)
            current_state[i] = new int[3];
        
        root_state = new int *[3];
        for (int i = 0; i < 3; i++)
            root_state[i] = new int[3];
        
        cumulativeCost = frontier.dequeue(current_state, root_state, &this->row, &this->col);
        if (Goal_Test(current_state))
        {
            getPath(root_state);
            printState(root_state);
            printState(current_state);
            return true;
        }
        
        explored[current_state] = root_state;
        
        //printState(current_state);
        Priority_next_state(this->current_state, this->row, this->col,cumulativeCost);
        
    }
    
    return false;
    
}

bool Puzzle::Goal_Test(int **current_state)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (current_state[i][j] != this->goal_state[i][j])
            {
                return false;
            }
        }
    }
    
    return true;
}

bool Puzzle::Goal_Test(int current_state[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (current_state[i][j] != this->goal_state[i][j])
            {
                return false;
            }
        }
    }
    
    return true;
}


bool Puzzle::next_state(int **current_state, int row, int col)
{
    int temp[3][3];
    
    if ((row + 1) < 3)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row + 1][col]);
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            if (Goal_Test(temp))
            {
                
                getPath(current_state);
                printState(current_state);
                printState(temp);
                return true;
            }
            else
                frontier.enqueue(temp, current_state, row + 1, col);
        }
        
    }
    
    if ((row - 1) >= 0)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row - 1][col]);
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            if (Goal_Test(temp))
            {
                getPath(current_state);
                printState(current_state);
                printState(temp);
                return true;
            }
            else
                frontier.enqueue(temp, current_state, row - 1, col);
        }
        
    }
    
    if ((col + 1) < 3)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row][col + 1]);
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            if (Goal_Test(temp))
            {
                getPath(current_state);
                printState(current_state);
                printState(temp);
                return true;
            }
            else
                frontier.enqueue(temp, current_state, row, col + 1);
        }
    }
    
    if ((col - 1) >= 0)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row][col - 1]);
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            if (Goal_Test(temp))
            {
                getPath(current_state);
                printState(current_state);
                printState(temp);
                return true;
            }
            else
                frontier.enqueue(temp, current_state, row, col - 1);
        }
    }
    
    return false;
    
}

void Puzzle::Priority_next_state(int **current_state, int row, int col,int cumulativeCost)
{
    int temp[3][3];
    int cost;
    
    if ((row + 1) < 3)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row + 1][col]);
        cost = Heuristic_func(temp) + cumulativeCost;
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            frontier.priority_enqueue(temp, current_state, row + 1, col,cost + 1,cumulativeCost);
        }
        else if (frontier.contains(temp))
        {
            frontier.updateNode(temp, current_state, cost + 1, cumulativeCost);
        }
        
    }
    
    if ((row - 1) >= 0)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row - 1][col]);
        cost = Heuristic_func(temp) + cumulativeCost;
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            frontier.priority_enqueue(temp, current_state, row - 1, col, cost + 1, cumulativeCost);
        }
        else if (frontier.contains(temp))
        {
            frontier.updateNode(temp, current_state, cost + 1, cumulativeCost);
        }
        
    }
    
    if ((col + 1) < 3)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row][col+1]);
        cost = Heuristic_func(temp) + cumulativeCost;
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            frontier.priority_enqueue(temp, current_state, row, col + 1, cost + 1, cumulativeCost);
        }
        else if (frontier.contains(temp))
        {
            frontier.updateNode(temp, current_state, cost + 1, cumulativeCost);
        }
    }
    
    if ((col - 1) >= 0)
    {
        copyArray(temp, current_state);
        swap(temp[row][col], temp[row][col - 1]);
        cost = Heuristic_func(temp) + cumulativeCost;
        
        if (!frontier.contains(temp) && !is_explored(temp))
        {
            frontier.priority_enqueue(temp, current_state, row, col - 1, cost + 1, cumulativeCost);
        }
        else if (frontier.contains(temp))
        {
            frontier.updateNode(temp, current_state, cost + 1, cumulativeCost);
        }
    }
    
    
}

bool Puzzle::is_explored(int current_state[3][3])
{
    
    for (auto x : explored)
    {
        if (compare(x.first, current_state) || compare(x.second, current_state))
            return true;
    }
    
    return false;
}

void Puzzle::shuffle(int initial_state[3][3])
{
    int i_arr[9];
    int row = 0;
    int col = 0;
    
    //initialize array with 9 random unique numbers ranging from [0-8]
    rand_array(i_arr);
    
    for (int i = 0; i < 9; i++)
    {
        if (col == 3)
        {
            col = 0;
            row++;
        }
        
        if (i_arr[i] == 0)
        {
            this->row = row;
            this->col = col;
        }
        
        initial_state[row][col] = i_arr[i];
        col++;
    }
}

void Puzzle::rand_array(int real_arr[9])
{
    int num;
    int count;
    srand(time(0));
    
    for (int i = 0; i < 9; i++)
    {
        num = rand() % 9;
        
        count = 1;
        
        while (count > 0)
        {
            count = 0;
            
            for (int j = 0; j < i; j++)
            {
                if (num == real_arr[j])
                {
                    count++;
                    num = rand() % 9;
                    break;
                }
            }
            
        }
        
        real_arr[i] = num;
    }
    
}

void Puzzle::swap(int &x, int &y)
{
    int temp = x;
    
    x = y;
    
    y = temp;
}

bool Puzzle::compare(int **move1, int move2[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (move1[i][j] != move2[i][j])
                return false;
        }
    }
    
    return true;
}

bool Puzzle::compare(int **move1, int **move2)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (move1[i][j] != move2[i][j])
                return false;
        }
    }
    
    return true;
}

//RECURSIVELY PRINT PATH TO GOAL STATE)
void Puzzle::getPath(int **solution)
{
    for (auto x : explored)
    {
        if (compare(solution, x.first))
        {
            if (!compare(x.second, null_matrix))
            {
                getPath(x.second);
                printState(x.second);
            }
            return;
        }
    }
    
}

void Puzzle::printState(int **state)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << state[i][j] << " ";
        
        cout << "\n";
    }
    
    cout << "\n";
    
}

void Puzzle::printState(int state[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << state[i][j] << " ";
        
        cout << "\n";
    }
    
    cout << "\n";
}

void Puzzle::findZero(int state[3][3], int *row, int *col)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            if (state[i][j] == 0)
            {
                *row = i;
                *col = j;
            }
    }
}

void Puzzle::findZero(int **state, int *row, int *col)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            if (state[i][j] == 0)
            {
                *row = i;
                *col = j;
            }
    }
}

void Puzzle::copyArray(int **to, int from[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            to[i][j] = from[i][j];
    }
    
}

void Puzzle::copyArray(int to[3][3], int **from)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            to[i][j] = from[i][j];
    }
    
}

int Puzzle::Heuristic_func(int state[3][3])
{
    int cost = 0;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->goal_state[i][j] != state[i][j])
                cost += manhattan_distance(state[i][j], i, j);
        }
    }
    
    return cost;
}

int Puzzle::manhattan_distance(int num, int row, int col)
{
    int man_dist = 0;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (goal_state[i][j] == num)
            {
                man_dist = (abs(i - row) + abs(j - col));
            }
        }
    }
    
    return man_dist;
}
