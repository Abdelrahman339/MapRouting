#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class edge {

private:



public:
	int node;
	float edgeLength;
	float edgeSpeed;

	edge();
	edge(int node,float edgeLength,float edgeSpeed);
	int getNode();
	float getlength();
	float getspeed();
	void printEdges(unordered_map<int, vector<edge>> edges);
};