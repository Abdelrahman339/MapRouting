#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

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
	vector<bestPath> p;
	float maxSpeed = -1;
	file f;

	auto startIO = high_resolution_clock::now();
	coor = f.readFile("map2", "[1] Sample Cases/input", graph, maxSpeed);
	queries = f.readQuery("[1] Sample Cases/input/queries2");

	//Input/Output after reading the query time starts

	int sourcePointId;
	int destinationPointID;
	//10 will be replaced with q.numberOfQueries
	for (query q : queries) {

		copyGraph = graph;
		copyCoor = coor;
		unordered_map<int, float> startPoints = getNodesWithinRadius(q.startCoordinate.x_coordinate, q.startCoordinate.y_coordinate, q.R, copyCoor);
		unordered_map<int, float> endPoints = getNodesWithinRadius(q.destCoordinate.x_coordinate, q.destCoordinate.y_coordinate, q.R, copyCoor);
		//add the start point and the distenation point in the graph for each qeuery
		sourcePointId = addNode(copyGraph, startPoints);
		destinationPointID = addNode(copyGraph, endPoints);
		addNode(copyCoor, q.startCoordinate);
		addNode(copyCoor, q.destCoordinate);

		A_Star path;
		p.push_back(path.A(copyGraph, sourcePointId, destinationPointID, maxSpeed, q.R, copyCoor));

	}

	f.writeFile("Output/output1.txt", p);

	auto stopIO = high_resolution_clock::now();
	double elapsedTimeWithIO = duration<float, milli>(stopIO - startIO).count();
	cout << "Not added yet" << " ms" << endl;
	cout << endl;
	cout << elapsedTimeWithIO << " ms" << endl;

	//cout << p.size();
	//	//a for loop will be added to display for each query
	//	while (!p.nodes.empty())
	//	{
	//		cout << p.nodes.top() << " ";
	//		p.nodes.pop();
	//	}
	//	cout << endl;
	//	cout << fixed << setprecision(2) << (p.time) << " mins" << endl;
	//	cout << fixed << setprecision(2) << (p.totalDistance) << " km" << endl;
	//	cout << fixed << setprecision(2) << (p.walkingDistance) << " km" << endl;
	//	cout << fixed << setprecision(2) << (p.roadDistance) << " km" << endl;
	//	cout << endl;
	//}


	return 0;
}