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
#include "../graph/edge.h"
#include "../graph/coordinates.h" 
#include "../helperFunction/helperFunctions.h"
#include "../query/query.h"
using namespace std;

class A_Star {

public:
	float f, h, g;



	float calcF(float h, float g);
	float calch(float n, coordinates destination, unordered_map<int, coordinates> coordinate,float maxSpeed,float R);
	float calcg(float startN, edge endN, float prevG);

	vector<int> findPath(vector<pair<int,float>> startPoints, vector<pair<int, float>>endPoints, coordinates DestPoint, unordered_map<int, vector<edge>> graph, unordered_map<int, coordinates> coordinate,float maxSpeed, vector<query> q);



};




