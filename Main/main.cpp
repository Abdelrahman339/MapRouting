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
	unordered_map<int, vector<edge>> copyGraph;
	unordered_map<int, coordinates> coordinates;
	vector<query> queries;
	bestPath bestPath;
	float maxSpeed = -1;
	file f;
	coordinates = f.readFile("map3", "[1] Sample Cases/input", graph, maxSpeed);
	queries = f.readQuery("[1] Sample Cases/input/queries3");


	int sourcePointId;
	int destinationPointID;
	//10 will be replaced with q.numberOfQueries
	for (query q : queries) {
		copyGraph = graph;

		unordered_map<int, float> startPoints = getNodesWithinRadius(q.startCoordinate.x_coordinate,q.startCoordinate.y_coordinate,q.R,coordinates);
		unordered_map<int, float> endPoints = getNodesWithinRadius(q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, q.R, coordinates);
		//add the start point and the distenation point in the graph for each qeuery
		sourcePointId = addNode(copyGraph, startPoints);
		destinationPointID = addNode(copyGraph, endPoints);
		addNode(coordinates,q.startCoordinate);
		addNode(coordinates,q.destCoordinate);
		


		A_Star path;
		//bestPath = path.findPath(startPoints, endPoints, queries[i].destCoordinate, graph, coordinates, maxSpeed, queries);
		vector<int> bestPath = path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, coordinates);



		//a for loop will be added to display for each query
		for (float node : bestPath)
			cout << node << " ";
		cout << endl;/*
		cout << truncateTwoDecimals(bestPath.time) << " mins" << endl;
		cout << truncateTwoDecimals(bestPath.roadDistance + bestPath.walkingDistance) << " km" << endl;
		cout << truncateTwoDecimals(bestPath.walkingDistance) << " km" << endl;
		cout << truncateTwoDecimals(bestPath.roadDistance) << " km" << endl;*/
		cout << endl;
	}

	return 0;
}