#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <deque>
using namespace std;

class bestPath
{
public:
	deque<int>nodes;
	double time;
	double roadDistance;
	double walkingDistance;
	double totalDistance;
};