# 8puzzle
AI project : Solving the 8puzzle game using breadth first search un-iformed search algorithm.

Project Members: Daniel Vilajeti

Test Runs:

Initial State = { {2,0,5} , {1,3,6} , {7,4,8} }; //Medium Difficulty

Initial State = { {1,2,0} , {3,4,5} , {6,7,8} }; //Easy Difficulty

Explanation of classes and their respective member functions:

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
test.solve("BFS"); ``` -> Solves randomly provided initial state using the breadth first search algortihm

```c++
bool breadth_first(int initial state[3][3]);
```
This member function will be called by ``` void test() ``` . The actual implementation of the algorith lives in this function
which returns ``` true ``` if a solution is found or ``` false ``` if no solution found.


bool next_state(int **state, int row, int col);
bool is_explored(int current_state[3][3]);
void shuffle(int initial_state[3][3]);
void rand_array(int real_arr[9]);
void getPath(int **solution);
void findZero(int state[3][3], int *row, int *col)


