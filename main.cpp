
#include <iostream>
#include <unordered_map>
#include "Puzzle.h"
#include "Queue.h"
using namespace std;


int main(int argc, const char * argv[]) {
    
    using namespace chrono;
    int arr[3][3] = {{2,0,5},{1,3,6},{7,4,8}};
    Puzzle test(arr);
   
    high_resolution_clock::time_point start_T = high_resolution_clock::now();
    test.solve();
    high_resolution_clock::time_point end_T = high_resolution_clock::now();
    
    cout << "The progrma took " << duration_cast<seconds>(end_T - start_T).count() << " seconds." << endl;
    
    system("pause");
    
    return 0;
}
