#include <iostream>
using namespace std;

//files
#include "../File/File.h" 
#include "../A_Star/A_Star.h"
#include "../helperFunction/helperFunctions.h"
//data structures
#include <unordered_map>
#include <vector>
#include <iomanip>




int main() {


	unordered_map<int, vector<edge>> graph;
	unordered_map<int, coordinates> coordinates;
	vector<query> queries;
	bestPath bestPath;
	float maxSpeed = -1;
	file f;
	coordinates = f.readFile("map2", "[1] Sample Cases/input", graph, maxSpeed);
	queries = f.readQuery("[1] Sample Cases/input/queries2");
	
	//10 will be replaced with q.numberOfQueries
	for (int i = 0; i < 10; i++)
	{


		unordered_map<int, float> startPoints = getNodesWithinRadius(queries[i].startCoordinate.x_coordinate, queries[i].startCoordinate.y_coordinate, queries[i].R, coordinates);
		unordered_map<int, float> endPoints = getNodesWithinRadius(queries[i].destCoordinate.x_coordinate, queries[i].destCoordinate.y_coordinate, queries[i].R, coordinates);
		A_Star path;
		bestPath = path.findPath(startPoints, endPoints, queries[i].destCoordinate, graph, coordinates, maxSpeed, queries);
		//a for loop will be added to display for each query
		for (float node : bestPath.nodes)
			cout << node << " ";
		cout << endl;
		cout << truncateTwoDecimals(bestPath.time) << " mins" << endl;
		cout << truncateTwoDecimals(bestPath.roadDistance + bestPath.walkingDistance) << " km" << endl;
		cout << truncateTwoDecimals(bestPath.walkingDistance) << " km" << endl;
		cout << truncateTwoDecimals(bestPath.roadDistance) << " km" << endl;
		cout << endl;
	}
	return 0;
}