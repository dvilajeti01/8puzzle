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
using namespace std;

void Puzzle::solve()
{
	if (!breadth_first(this->initial_state))
		cout << "NOT SOLVE-ABLE";
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

		frontier.dequeue(current_state, root_state, this->row, this->col);

		explored[current_state] = root_state;
		//memcpy(explored[this->current_state], this->root_state, sizeof(this->current_state));

		if (next_state(this->current_state, this->row, this->col))
		{
			return true;
		}

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
		for (int i = 0; i < 3; i++)
		{
			memcpy(*(temp + i), *(current_state + i), sizeof(*temp));
		}

		swap(temp[row][col], temp[row + 1][col]);



		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				printState(temp);
				getPath(current_state);
				return true;
			}
			else
				frontier.enqueue(temp,current_state, row + 1, col);
		}


	}

	if ((row - 1) >= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			memcpy(*(temp + i), *(current_state + i), sizeof(*temp));
		}

		swap(temp[row][col], temp[row - 1][col]);



		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				printState(temp);
				getPath(current_state);
				return true;
			}
			else
				frontier.enqueue(temp, current_state, row - 1, col);
		}

	}

	if ((col + 1) < 3)
	{
		for (int i = 0; i < 3; i++)
		{
			memcpy(*(temp + i), *(current_state + i), sizeof(*temp));
		}

		swap(temp[row][col], temp[row][col + 1]);



		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				printState(temp);
				getPath(current_state);
				return true;
			}
			else
				frontier.enqueue(temp, current_state, row, col + 1);
		}
	}

	if ((col - 1) >= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			memcpy(*(temp + i), *(current_state + i), sizeof(*temp));
		}

		swap(temp[row][col], temp[row][col - 1]);



		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				printState(temp);
				getPath(current_state);
				return true;
			}
			else
				frontier.enqueue(temp, current_state, row, col - 1);
		}
	}

	return false;

}

bool Puzzle::is_explored(int current_state[3][3])
{

	for (auto const& x : explored)
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

bool Puzzle::compare(int **move1,int move2[3][3])
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

//RECURSIVELY RUN UNTIL YOU HIT NULL PARENT(0)
void Puzzle::getPath(int **solution)
{
	
	if (compare(solution,null_vector))
		return;
	else
	{
		printState(explored.at(solution));
		getPath(explored.at(solution));
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

}

void Puzzle::printState(int state[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << state[i][j] << " ";

		cout << "\n";
	}
}

void Puzzle::findZero(int state[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			if (state[i][j] == 0)
			{
				this->row = i;
				this->col = j;
			}
	}
}
