
#include <iostream>
#include <unordered_map>
#include "Puzzle.h"
#include "Queue.h"
#include <chrono>
using namespace std;


int main(int argc, const char * argv[]) {

	using namespace chrono;

	



	int arr[3][3] = { { 2, 0, 5 },{ 1, 3, 6 },{ 7, 4, 8 } };
    int arr2[3][3] = { { 1, 2, 0 },{ 3, 4, 5 },{ 6, 7, 8 } };
	Puzzle test(arr);
	

	high_resolution_clock::time_point start_T = high_resolution_clock::now();
	test.solve();
	high_resolution_clock::time_point end_T = high_resolution_clock::now();

	cout << "The progrma took " << duration_cast<milliseconds>(end_T - start_T).count() << " milliseconds.\n" << endl;

	Puzzle test2(arr2);
	

	start_T = high_resolution_clock::now();
	test2.solve();
	end_T = high_resolution_clock::now();

	cout << "The progrma took " << duration_cast<milliseconds>(end_T - start_T).count() << " milliseconds." << endl;

	system("pause");

	return 0;
}
