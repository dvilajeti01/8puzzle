#pragma once

//
//  Puzzle.h
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright © 2019 Daniel Vilajeti. All rights reserved.
//


#include "Queue.h"
#include <unordered_map>


class Puzzle
{
private:


	int initial_state[3][3] = { {1,2,3},{4,5,6},{7,8,0} };
	int goal_state[3][3];

	Queue explored;
	Queue frontier;


public:



	~Puzzle()
	{
		shuffle(initial_state);
		goal_state[3][3] = { { 0,1,2 },{ 3,4,5 },{ 6,7,8 } };
	}


	void solve();

	bool breadth_first(int initial_state[3][3], Queue explored, Queue frontier);

	bool Goal_Test(int initial_state[3][3], int goal_state[3][3]);

	void next_state(int current_state[3][3]);

	bool explored(int current_state[3][3]);

	void shuffle(int initial_state[3][3]);
	
	void rand_array(int real_arr[3]);
	




};


