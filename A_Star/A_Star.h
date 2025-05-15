#pragma once

//f(n) = g(n) + h(n)
//g(n): Actual time taken from the start to node n (walking + driving).
//h(n) : Optimistic estimate of time from n to the destination(heuristic) => el node ely wa2f 3andaha

//Steps
//1) Determine valid start/end nodes
//2) Initialize A*
//3) Explore Nodes
//4) terminate when optimal path is found

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include "../graph/edge.h"
#include "../graph/coordinates.h" 
#include "../helperFunction/helperFunctions.h"
#include "../query/query.h"
#include "../bestPath/bestPath.h"

using namespace std;

class A_Star {

public:
	double f, h, g;



	double calcF(double h, double g);
	double calcH(int startPointID, int destinationPointId, unordered_map<int, coordinates> coordinate, double maxSpeed, double R);
	double calcG(int startN, edge endN, double prevG,double index);
	double calcG(int startN, edge endN, double prevG);

	double calcHForEndpoint(int nodeId, const unordered_map<int, double>& endPoints, const unordered_map<int, coordinates>& coordinate, double maxSpeed, double R);

	bestPath A(unordered_map<int, vector<edge>> graph, int sourcePointID, int destinationPointID, double maxSpeed, double R, unordered_map<int, coordinates>, double timeIntervel, int speedSize);
	
	bestPath A(const unordered_map<int, vector<edge>>& graph, int sourcePointID, int destinationPointID, double maxSpeed, double R, const unordered_map<int, coordinates>&);

};


struct NodeInfo {
	int node;
	double fCost;
	double walkDist;
	double roadDist;
	double walkTime;
	double roadTime;

	// Priority queue comparator (min-heap)
	bool operator>(const NodeInfo& other) const {
		return fCost > other.fCost;
	}
};

