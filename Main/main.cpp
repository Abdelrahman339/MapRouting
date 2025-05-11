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
	queries = f.readQuery("[1] Sample Cases/input/queries2");
	unordered_map<int, float> startPoints = getNodesWithinRadius(queries[0].startCoordinate.x_coordinate, queries[0].startCoordinate.y_coordinate, queries[0].R, coordinates);
	unordered_map<int, float> endPoints = getNodesWithinRadius(queries[0].destCoordinate.x_coordinate, queries[0].destCoordinate.y_coordinate, queries[0].R, coordinates);
	A_Star path;
	bestPath = path.findPath(startPoints, endPoints, queries[0].destCoordinate, graph, coordinates, maxSpeed, queries);

	//a for loop will be added to display for each query
	for (float node : bestPath.nodes)
		cout << node <<" ";
	cout<<endl;
	cout << bestPath.time <<" mins" << endl;
	cout << bestPath.roadDistance + bestPath.walkingDistance << " km"<< endl;
	cout << bestPath.walkingDistance << " km"<< endl;
	cout << bestPath.roadDistance << " km"<< endl;

	return 0;
}