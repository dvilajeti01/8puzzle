//
//  Puzzle.cpp
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/4/19.
//  Copyright © 2019 Daniel Vilajeti. All rights reserved.
//

#include <stdio.h>
#include "Puzzle.h"
#include <iostream>
#include <unordered_map>
using namespace std;

bool Puzzle::Goal_Test(int initial_state[3][3], int goal_state[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (initial_state[i][j] != goal_state[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

void Puzzle::next_state(int current_state[3][3])
{

}

void Puzzle::shuffle(int initial_state[3][3])
{

	unordered_map<int, int[3]> order;
	int i_arr[3];
	
	//POPULATE ORDERED MAP WHICH REPRESENTS THE INDEXES OF A SHUFFLED 2-D ARRAY
	for (int i = 0; i < 3; i++)
	{
		rand_array(order[i_arr[i]]);

	}

	int temp[3][3];
	//COPY INITIAL ARRAY ELEMENTS TO TO TEMP ARRAY
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = initial_state[i][j];
		}
	}

	//SHUFFLE 2-D ARRAY
	for (auto i = order.begin(); i != order.end(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				initial_state[j][k] = temp[i->first][i->second[k]];
			}
			i++;
		}
	}


}

void Puzzle::rand_array(int real_arr[3])
{
	int count = 0;
	int num;
	bool exists = 0;

	//INITIALIZES AN ARRAY WITH 3 DISTINCT RANDOM NUMBERS RANGING FROM 0-2(inclusive)
	for (int i = 2; i >= 0; i--)
	{
		count = 0;
		
		while (count == 0)
		{
			num = rand() % 3;

			for (int j = i + 1; j < 3; j++)
			{
				if (real_arr[j] == num)
				{
					exists = true;
					break;
				}
				else
					exists = false;
			}

			if (exists == false)
			{
				real_arr[i] = num;
				count = 1;
			}
		}
	}


}
