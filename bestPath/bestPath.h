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
	float time;
	float roadDistance;
	float walkingDistance;
	float totalDistance;
};