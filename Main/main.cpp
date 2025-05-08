#include <iostream>
using namespace std;

//files
#include "../File/File.h" 


//data structures
#include <unordered_map>
#include <vector>




int main() {

	unordered_map<int, vector<edge>> graph;
	unordered_map<int, coordinates> coordinates;


	file f;
	coordinates=f.readFile("map2", "[1] Sample Cases/input",graph);



	return 0;
}