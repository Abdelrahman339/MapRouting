#pragma once
#include "../graph/edge.h"
#include "../graph/coordinates.h"
#include "../query/query.h"
#include "../helperFunction/helperFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iomanip>



using namespace std;

class file {


public:

	void readFile(string fileName,  unordered_map<int, vector<edge>>& graph, double& maxSpeed,unordered_map <int, coordinates>& Nodes);
	void readFile(string fileName,unordered_map<int,vector<edge>>&graph,double &maxSpeed, double& Speed_Interval, int& speedSize, unordered_map <int, coordinates>& Nodes);
	void writeFile(string fileName,vector<bestPath> quries);
	string getCellKey(double x, double y, double cellSize);

	void readQuery(string fileName, vector<query> &queries);


};