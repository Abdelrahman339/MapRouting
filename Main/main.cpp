#include <iostream>
using namespace std;

//files
#include "../File/File.h" 


//data structures
#include <unordered_map>
#include <vector>




int main() {

	//using variables
	unordered_map<int, vector<edge>> graph;
	unordered_map<int, coordinates> coordinates;
	vector<query> queries;
	float maxSpeed;
	file f;
	coordinates = f.readFile("map2", "[1] Sample Cases/input", graph,maxSpeed);
	queries = f.readQery("[1] Sample Cases/input/queries1");


	return 0;
}