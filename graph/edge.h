#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class edge {

private:



public:
	int node;
	double edgeLength;
	vector<double> edgeSpeeds;
	double edgeSpeed;
	double cost;//the time cost that used in all the calculation 
	edge();
	edge(int node,double edgeLength,double edgeSpeed);
	int getNode();
	double getlength();
	double getspeed();
	void printEdges(unordered_map<int, vector<edge>> edges);
};