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
	node *newNode = nullptr;

	newNode = new node;

	memcpy(newNode->move,move,sizeof(newNode->move));

	for (int i = 0; i < 3; i++)
	{
		memcpy(*(newNode->root_move + i), *(root_move + i), sizeof(*newNode->root_move));
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

void Queue::dequeue(int **move, int **root_move, int &row, int &col)
{
	node *temp = nullptr;

	if (isEmpty())
	{
		cout << "Queue is empty!\n";
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			memcpy(*(move+i), *(front->move + i), sizeof(*move));
		}
		for (int i = 0; i < 3; i++)
		{
			memcpy(*(root_move + i), *(front->root_move + i), sizeof(*root_move));
		}
		
		row = front->row;
		col = front->col;

		temp = front;
		front = front->next;
		delete temp;

		num_items--;

	}
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
