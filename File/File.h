#pragma once
#include "../graph/edge.h"
#include "../graph/coordinates.h"
#include "../query/query.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>


using namespace std;

class file {


public:
	unordered_map<int, coordinates> readFile(string fileName,string typeOftest,unordered_map<int,vector<edge>>&graph,float &maxSpeed);
	unordered_map<int, coordinates> writeFile(string fileName, string typeOftest);

	vector<query> readQery(string fileName);


};