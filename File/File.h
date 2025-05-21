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
#include <chrono>



using namespace std;

class file {


public:

	void readFile(string fileName,  unordered_map<int, vector<edge>>& graph, double& maxSpeed,vector<coordinates>& Nodes);
	void writeFile(string fileName,vector<bestPath> quries,double timeWithIO, double elapsedTimeWithouttIO);
	

	void readQuery(string fileName, vector<query> &queries);


};