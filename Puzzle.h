#pragma once

//
//  Puzzle.h
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright 2019 Daniel Vilajeti. All rights reserved.
//


#include "Queue.h"
#include "LinkedList.h"
#include <unordered_map>
using namespace std;


class Puzzle
{
private:

	//Stores initial state
	int initial_state[3][3];

	//Stores goal state (immutable for now)
	int goal_state[3][3] = { { 0, 1, 2 },{ 3, 4, 5 },{ 6, 7, 8 } };

	//Stores the latest popped state
	int current_state[3][3];

	//stores the root state of the latest popped state
	int root_state[3][3];

	//Row location of the 0 of the latest popped state
	int row;

	//Row location of the 0 of the latest popped state
	int col;

	//Queue of the frontier
	Queue frontier;

	//Mapp of the explored states (key: state, value: root state)
	unordered_map <int[3][3], int[3][3] > explored;

public:


	//Deffault constructor which produces a randomly generated initial state
	Puzzle()
	{
		shuffle(initial_state);
	}

	//MEMBER FUNCTIONS

	//Solve the the 8 Puzzle problem
	void solve();

	//non-informed breadth first search algorithim
	bool breadth_first(int initial_state[3][3]);

	//Tests if given state is the goal state
	bool Goal_Test(int current_state[3][3]);

	//Producess next state
	bool next_state(int current_state[3][3], int row, int col);

	//Checks if given state exists in the explored map
	bool is_explored(int current_state[3][3]);

	//Shuffles the initial state
	void shuffle(int initial_state[3][3]);

	//Generates 3 unique numbers in the range [0-2]
	void rand_array(int real_arr[3]);

	//Swaps two given values
	void swap(int &x, int &y);

	//Compares two 2-d arrays
	bool compare(const int move1[3][3], const int move2[3][3]);

	//Finds the path produced by the search algorithm
	void getPath(const int solution[3][3]);

	//Prints the state to screen
	void printState(const int state[3][3]);

};
