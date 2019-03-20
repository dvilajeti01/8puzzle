#pragma once

//
//  Breadth_First_Search.h
//  AI_Project1
//
//  Created by Daniel Vilajeti on 3/3/19.
//  Copyright © 2019 Daniel Vilajeti. All rights reserved.
//


class Queue
{
private:
	struct node
	{
		int value;
		node *next;
	};

	node *front;
	node *rear;
	int num_items;

public:

	Queue();

	~Queue();

	void enqueue(int num);

	void dequeue(int &x);

	bool isEmpty();

	void clear();


};


