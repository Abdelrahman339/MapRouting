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
	unordered_map<int, coordinates> readFile(string fileName,string typeOftest,unordered_map<int,vector<edge>>&graph,float &maxSpeed);
	void writeFile(string fileName,vector<bestPath> quries);

	vector<query> readQuery(string fileName);


};