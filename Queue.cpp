//
//  Breadth_First_Search.cpp
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright 2019 Daniel Vilajeti. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "Queue.h"


using namespace std;

Queue::Queue()
{
	front = nullptr;
	rear = nullptr;
	num_items = 0;
}

Queue::~Queue()
{
	clear();
}

void Queue::enqueue(int move[3][3], int **root_move, int row, int col)
{
	int null_matrix[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
	node *newNode = nullptr;

	newNode = new node;

	memcpy(newNode->move, move, sizeof(newNode->move));

	if (root_move == NULL)
	{
		//MAKE NULL VECTOR
		memcpy(newNode->root_move, null_matrix, sizeof(newNode->root_move));

	}
	else
	{
		copyArray(newNode->root_move, root_move);
	}


	newNode->row = row;
	newNode->col = col;
	newNode->next = nullptr;

	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	else
	{
		rear->next = newNode;
		rear = newNode;
	}

	num_items++;
}

void Queue::priority_enqueue(int move[3][3], int ** root_move, int row, int col, int cost, int parent_cost)
{
	int null_matrix[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
	node *newNode = nullptr;

	newNode = new node;

	node *temp;
	temp = front;


	memcpy(newNode->move, move, sizeof(newNode->move));

	if (root_move == NULL)
	{
		//MAKE NULL VECTOR
		memcpy(newNode->root_move, null_matrix, sizeof(newNode->root_move));

	}
	else
	{
		copyArray(newNode->root_move, root_move);
	}


	newNode->row = row;
	newNode->col = col;
	newNode->cost = cost;
	newNode->parent_cost = parent_cost;
	newNode->next = nullptr;

	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	else
	{
		if (front->cost > cost)
		{
			newNode->next = front;
			front = newNode;
		}
		else
		{
			while (temp->next != nullptr && temp->next->cost <= cost)
				temp = temp->next;

			newNode->next = temp->next;
			temp->next = newNode;
		}
	}

	num_items++;
}

int Queue::dequeue(int **move, int **root_move, int *row, int *col)
{
	node *temp = nullptr;
	int null_matrix[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
	int parent_cost;

	if (isEmpty())
	{
		cout << "Queue is empty!\n";
	}
	else
	{
		copyArray(move, front->move);


		if (compare(front->root_move, null_matrix))
		{
			//MAKE NULL VECTOR
			copyArray(root_move, null_matrix);

		}
		else
		{
			copyArray(root_move, front->root_move);
		}


		*row = front->row;
		*col = front->col;
		parent_cost = front->parent_cost;
		temp = front;
		front = front->next;
		delete temp;

		num_items--;

	}

	return parent_cost;
}

void Queue::dequeue()
{
	node *temp = nullptr;

	if (isEmpty())
	{
		cout << "Queue is empty!\n";
	}
	else
	{
		temp = front;
		front = front->next;
		delete temp;

		num_items--;

	}
}
bool Queue::isEmpty()
{
	if (num_items > 0)
		return false;
	else
		return true;
}

void Queue::clear()
{
	while (!isEmpty())
		dequeue();
}

bool Queue::contains(int move[3][3])
{
	node *temp;

	temp = front;
	for (int i = 0; i < num_items; i++)
	{
		if (compare(temp->move, move))
			return true;
		else
			temp = temp->next;
	}
	return false;
}

bool Queue::compare(int move[3][3], int move2[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (move[i][j] != move2[i][j])
				return false;
		}
	}

	return true;
}

void Queue::copyArray(int **to, int from[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			to[i][j] = from[i][j];
	}
}
void Queue::copyArray(int to[3][3], int **from)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			to[i][j] = from[i][j];
	}
}

void Queue::updateNode(int state[3][3],int **root_state, int cost, int cumulative_cost)
{
	node *temp;

	temp = front;
	for (int i = 0; i < num_items; i++)
	{
		if (compare(temp->move, state))
		{
			if (temp->cost > cost)
			{
				temp->cost = cost;
				temp->parent_cost = cumulative_cost;
				copyArray(temp->root_move, root_state);
				return;
			}
		}
		else
			temp = temp->next;
	}
	
}
