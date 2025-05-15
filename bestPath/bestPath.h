#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

class bestPath
{
public:
	stack<int>nodes;
	double time;
	double roadDistance;
	double walkingDistance;
	double totalDistance;
};