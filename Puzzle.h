#pragma once

//
//  Puzzle.h
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright � 2019 Daniel Vilajeti. All rights reserved.
//


#include "Queue.h"
#include "LinkedList.h"
#include <unordered_map>
using namespace std;


class Puzzle
{
private:


	int initial_state[3][3];
	int goal_state[3][3] = { { 0, 1, 2 },{ 3, 4, 5 },{ 6, 7, 8 } };
    
    int current_state[3][3];
    int root_state[3][3];
    int row;
    int col;

	Queue frontier;
    unordered_map <int[3][3],int[3][3] > explored;

public:



	Puzzle()
	{
		shuffle(initial_state);
	}


	void solve();

	bool breadth_first(int initial_state[3][3]);

	bool Goal_Test(int current_state[3][3]);

	bool next_state(int current_state[3][3],int row, int col);

	bool is_explored(int current_state[3][3]);

	void shuffle(int initial_state[3][3]);
	
	void rand_array(int real_arr[3]);
	
	void swap(int &x, int &y);

	bool compare(const int move1[3][3], const int move2[3][3]);
    
    void printSolution(int solution[3][3]);

};

