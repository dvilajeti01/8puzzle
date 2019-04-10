# 8puzzle
AI project : Solving the 8puzzle game using breadth first search un-iformed search algorithm.

Project Members: Daniel Vilajeti

Test Runs:

Initial State = { {2,0,5} , {1,3,6} , {7,4,8} }; //Medium Difficulty

Initial State = { {1,2,0} , {3,4,5} , {6,7,8} }; //Easy Difficulty

# Explanation of the ``` Puzzle ``` class and its respective member functions:

``` Puzzle.h ```

Creating an object of type ``` Puzzle ``` will create a new instance of the puzzle with it's own initial state, goal state , frontier queue used to store possible moves
and explored unordered_map which stores all attemped moves.

Using the default constructor initial state will be a randomly shuffled goal state. (This may produce an un-solveable initial state)
Instead you may pass your own initial state when creating an object of ``` Puzzle ``` type.

The ``` Puzzle ``` class key member functions:

``` c++
void solve();

```

Calling this function will attmept to solve the puzle, if the attempt is succeful the path from the initial state to
the goal state is printed including the time it took to solve the problem (in milliseconds) else a message will be provided informing the user
there was no solution found. Currently there is only one algorithm present.
In the near future(~1-2 weeks) you will be able to choose between A* search or Breadth First Search by passing
the option as a parameter.

For example:

``` c++
Puzzle test;
test.solve("BFS"); -> Solves randomly provided initial state using the breadth first search algortihm

``` 

``` c++
bool breadth_first(int initial state[3][3]);

```
This member function will be called by ``` void test() ``` . The actual implementation of the algorith lives in this function
which returns ``` true ``` if a solution is found or ``` false ``` if no solution found.

``` c++
bool next_state(int **state, int row, int col);
```

``` next_state ``` generates all possible moves for a given moves based on the location of the empty square or "0".
There may be at most 4 moves generated and once the move is generated the goal test is applied before appending to the queue.

``` c++
bool is_explored(int current_state[3][3]);
```

``` is_explored ``` tests for the existence of given state within the explored unordered map in which it will return ``` true ``` if found or otherwise ``` false ```.

``` c++
void shuffle(int initial_state[3][3]);
void rand_array(int real_arr[9]);

```

The ``` shuffle ``` function shuffles a given state by calling ``` rand_array ``` which produces an array of 9 unique numbers between [0-9] and maps these values to a 2D array.

``` c++
void getPath(int **solution);
```

``` getPath ``` prints the path from a given state to the initial state. This is implemented by recursively printing the root state(excluding null matrix) of a given state until initial state is reached.

# Explanation of the data structures and containers used

All moves are first stored in the frontier which is implemented as a FIFO Queue. The Queue is made up of nodes where each node contains a state/move, the corresponding root move/state from which the move/state derived from, the row and col index where the empty square lies and a pointer to the next node.



```
NODE
=====================
MOVE               ||
-----------------  ||
[ 0 2 5 ] row = 0  ||
[ 1 3 6 ] col = 0  ||
[ 7 4 8 ]          ||
          *pointer -------------|  
ROOT MOVE          ||           |
----------------   ||           |
[ 2 0 5 ]          ||           |
[ 1 3 6 ]          ||           |
[ 7 4 8 ]          ||           |
=====================           |
                                |
NODE                            |
=====================           |
MOVE               ||<----------|
-----------------  ||
[ 2 0 5 ] row = 0  ||
[ 1 3 6 ] col = 1  ||
[ 7 4 8 ]          ||
          *pointer -------------|  
ROOT MOVE          ||           |
----------------   ||           |
[ 2 5 0 ]          ||           |
[ 1 3 6 ]          ||           |
[ 7 4 8 ]          ||           |
=====================           |
                                |
NODE                            |
=====================           |
MOVE               ||<----------|
-----------------  ||
[ 2 5 0 ] row = 0  ||
[ 1 3 6 ] col = 2  ||
[ 7 4 8 ]          ||
          *pointer -------------|  
ROOT MOVE          ||           |
----------------   ||           |
[ 2 5 6 ]          ||           |
[ 1 3 0 ]          ||           |
[ 7 4 8 ]          ||           |
=====================           |
                                |
NODE                            |
=====================           |
MOVE               ||<----------|
-----------------  ||
[ 2 5 6 ] row = 1  ||
[ 1 3 0 ] col = 2  ||
[ 7 4 8 ]          ||
          *pointer ---------------> NULL  
ROOT MOVE          ||           
----------------   ||           
[ 2 5 6 ]          ||           
[ 1 3 8 ]          ||           
[ 7 4 0 ]          ||           
=====================           

```

Once a move is dequed from the Queue it is considered "explored" and added to the ``` unordered_map ```. The move is mapped a the ```key``` and its corresponding root move is the ```value```. All the keys in the map are unique.


```

KEY           VALUE

[ 2 0 5 ]     [ 0 0 0 ]
[ 1 3 6 ]     [ 0 0 0 ]
[ 7 4 8 ]     [ 0 0 0 ]


[ 2 5 0 ]     [ 2 0 5 ]
[ 1 3 6 ]     [ 1 3 6 ]
[ 7 4 8 ]     [ 7 4 8 ]


[ 2 5 6 ]     [ 2 5 0 ]
[ 1 3 0 ]     [ 1 3 6 ]
[ 7 4 8 ]     [ 7 4 8 ]

```
