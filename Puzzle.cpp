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
	breadth_first(this->initial_state);
}

bool Puzzle::breadth_first(int initial_state[3][3])
{
	if (Goal_Test(initial_state))
	{
		getPath(initial_state);
		return true;
	}

	frontier.enqueue(initial_state, NULL, this->row, this->col);

	while (!frontier.isEmpty())
	{
		frontier.dequeue(current_state, root_state, this->row, this->col);

		memcpy(explored[this->current_state], this->root_state, sizeof(this->current_state));

		if (next_state(this->current_state, this->row, this->col))
		{
			return true;
		}

	}

	return false;
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

bool Puzzle::next_state(int current_state[3][3], int row, int col)
{
	int temp[3][3];

	if ((row + 1) < 3)
	{
		memcpy(temp, current_state, sizeof(temp));
		swap(temp[row][col], temp[row + 1][col]);

		

		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				getPath(temp);
				return true;
			}
			else
				frontier.enqueue(current_state, temp, row + 1, col);
		}


	}

	if ((row - 1) >= 0)
	{
		memcpy(temp, current_state, sizeof(temp));
		swap(current_state[row][col], current_state[row - 1][col]);

		
		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				getPath(temp);
				return true;
			}
			else
				frontier.enqueue(current_state, temp, row - 1, col);
		}

	}

	if ((col + 1) < 3)
	{
		memcpy(temp, current_state, sizeof(temp));
		swap(temp[row][col], temp[row][col + 1]);


		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				getPath(temp);
				return true;
			}
			else
				frontier.enqueue(current_state, temp, row, col + 1);
		}
	}

	if ((col - 1) >= 0)
	{
		memcpy(temp, current_state, sizeof(temp));
		swap(temp[row][col], temp[row][col - 1]);


		if (!frontier.contains(temp) && !is_explored(temp))
		{
			if (Goal_Test(temp))
			{
				getPath(temp);
				return true;
			}
			else
				frontier.enqueue(current_state, temp, row, col - 1);
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
	unordered_map<int, int[3]> order;
	int i_arr[3];

	//POPULATE ORDERED MAP WHICH REPRESENTS THE INDEXES OF A SHUFFLED 2-D ARRAY
	for (int i = 0; i < 3; i++)
	{
		rand_array(order[i_arr[i]]);

	}

	int temp[3][3];
	//COPY INITIAL ARRAY ELEMENTS TO TO TEMP ARRAY
	memcpy(temp, initial_state, sizeof(temp));

	//SHUFFLE 2-D ARRAY
	for (auto i = order.begin(); i != order.end(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				initial_state[j][k] = temp[i->first][i->second[k]];
				if (initial_state[j][k] == 0) //store location of zero
				{
					this->row = j;
					this->col = k;
				}
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

void Puzzle::swap(int &x, int &y)
{
	int temp = x;

	x = y;

	y = temp;
}

bool Puzzle::compare(const int move1[3][3], const int move2[3][3])
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

//RECURSIVELY RUN UNTIL YOU HIT NULL
void Puzzle::getPath(const int solution[3][3])
{
	unordered_map <int[3][3], int[3][3] > ::iterator i;

	if (solution == NULL)
		return;
	else
	{
		for (i = explored.begin(); i != explored.end(); i++)
		{
			if (compare(i->first, solution))
			{
				printState(solution);
				getPath(i->second);
			}
		}
	}
	

}

void Puzzle::printState(const int state[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << state[i][j] << " ";
		}

		cout << endl;
	}

	cout << "\n";
}
