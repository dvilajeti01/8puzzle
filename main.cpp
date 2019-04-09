
#include <iostream>
#include <unordered_map>
#include "Puzzle.h"
#include "Queue.h"
#include <chrono>
using namespace std;


int main(int argc, const char * argv[]) {

	using namespace chrono;

	int **arr1 = new int *[3];
	for (int i = 0; i < 3; i++)
		arr1[i] = new int[3];



	//int arr[3][3] = { { 1,2,3 },{ 4,5,6 },{ 7,8,0 } };
	Puzzle test;
	test.getInitialState(arr1);
	test.printState(arr1);

	high_resolution_clock::time_point start_T = high_resolution_clock::now();
	test.solve();
	high_resolution_clock::time_point end_T = high_resolution_clock::now();

	cout << "The progrma took " << duration_cast<milliseconds>(end_T - start_T).count() << " milliseconds.\n" << endl;

	Puzzle test2;
	test2.getInitialState(arr1);
	test2.printState(arr1);

	start_T = high_resolution_clock::now();
	test2.solve();
	end_T = high_resolution_clock::now();

	cout << "The progrma took " << duration_cast<milliseconds>(end_T - start_T).count() << " milliseconds." << endl;

	system("pause");

	return 0;
}