#include <iostream>
#include <chrono>


using namespace std;
using namespace std::chrono;

//files
#include "../File/File.h" 
#include "../A_Star/A_Star.h"
#include "../helperFunction/helperFunctions.h"
#include "../Test/test.h";
//data structures
#include <unordered_map>
#include <vector>
#include <iomanip>




int main() {
	 
	cout << "Map routing\n";

	cout << "[1] Sample Test. [2] Meduim Test. [3] Large Test. [4] Bouns Test. [6] visual\n";
	char choice;
	cin >> choice;
	
	test t;

	t.displayTest(choice);


	return 0;
}