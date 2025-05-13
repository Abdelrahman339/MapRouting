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
	unordered_map<int, coordinates> coor;
	unordered_map<int, coordinates> copyCoor;
	vector<query> queries;
	bestPath p;
	float maxSpeed = -1;
	file f;
	coor = f.readFile("map2", "[1] Sample Cases/input", graph, maxSpeed);
	queries = f.readQuery("[1] Sample Cases/input/queries2");


	int sourcePointId;
	int destinationPointID;
	//10 will be replaced with q.numberOfQueries
	for (query q : queries) {

		copyGraph = graph;
		copyCoor = coor;
		unordered_map<int, float> startPoints = getNodesWithinRadius(q.startCoordinate.x_coordinate,q.startCoordinate.y_coordinate,q.R, copyCoor);
		unordered_map<int, float> endPoints = getNodesWithinRadius(q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, q.R, copyCoor);
		//add the start point and the distenation point in the graph for each qeuery
		sourcePointId = addNode(copyGraph, startPoints);
		destinationPointID = addNode(copyGraph, endPoints);
		addNode(copyCoor,q.startCoordinate);
		addNode(copyCoor,q.destCoordinate);
		


		A_Star path;
		//bestPath = path.findPath(startPoints, endPoints, queries[i].destCoordinate, graph, coordinates, maxSpeed, queries);
		vector<int> bestPath = path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor,p);



		//a for loop will be added to display for each query
		for (float node : bestPath)
			cout << node << " ";
		cout << endl;
		cout << truncateTwoDecimals(p.time) << " mins" << endl;
		cout << truncateTwoDecimals(p.roadDistance + p.walkingDistance) << " km" << endl;
		cout << truncateTwoDecimals(p.walkingDistance) << " km" << endl;
		cout << truncateTwoDecimals(p.roadDistance) << " km" << endl;
		cout << endl;
	}

	return 0;
}