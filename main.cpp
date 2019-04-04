
#include <iostream>
#include <chrono>
#include "Puzzle.h"
using namespace std;


int main() 
{
	using namespace chrono;
	Puzzle test;

	high_resolution_clock::time_point start_T = high_resolution_clock::now();
	test.solve();
	high_resolution_clock::time_point end_T = high_resolution_clock::now();
	
	cout << "The progrma took " << duration_cast<seconds>(end_T - start_T).count() << " seconds." << endl;

	return 0;
}
