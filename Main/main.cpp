#include <iostream>
using namespace std;

//files
#include "../File/File.h" 
#include "../A_Star/A_Star.h"
#include "../helperFunction/helperFunctions.h"
//data structures
#include <unordered_map>
#include <vector>




int main() {


	unordered_map<int, vector<edge>> graph;
	unordered_map<int, coordinates> coordinates;
	vector<query> queries;
	bestPath bestPath;
	float maxSpeed = -1;
	file f;
	coordinates = f.readFile("map2", "[1] Sample Cases/input", graph, maxSpeed);
	queries = f.readQery("[1] Sample Cases/input/queries2");
	unordered_map<int, float> startPoints = getNodesWithinRadius(queries[7].startCoordinate.x_coordinate, queries[7].startCoordinate.y_coordinate, queries[7].R, coordinates);
	unordered_map<int, float> endPoints = getNodesWithinRadius(queries[7].destCoordinate.x_coordinate, queries[7].destCoordinate.y_coordinate, queries[7].R, coordinates);
	A_Star path;
	bestPath = path.findPath(startPoints, endPoints, queries[7].destCoordinate, graph, coordinates, maxSpeed, queries);

	cout << "the path:\n";
	for (float node : bestPath.nodes)
		cout << "node: " << node << endl;
	return 0;
}