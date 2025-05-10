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
	float maxSpeed;
	file f;
	coordinates = f.readFile("map1", "[1] Sample Cases/input", graph, maxSpeed);
	queries = f.readQery("[1] Sample Cases/input/queries1");
	vector<pair<int, float>> startPoints=getNodesWithinRadius(queries[0].startCoordinate.x_coordinate, queries[0].startCoordinate.y_coordinate, queries[0].R,coordinates);
	vector<pair<int, float>> endPoints =getNodesWithinRadius(queries[0].destCoordinate.x_coordinate, queries[0].destCoordinate.y_coordinate, queries[0].R,coordinates);
	A_Star path;
	path.findPath(startPoints, endPoints, queries[0].destCoordinate, graph, coordinates, 80, queries);

	return 0;
}