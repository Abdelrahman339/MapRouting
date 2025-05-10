#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class bestPath
{
public:
	int startNodeId;
	unordered_set<int>nodes;
	float time;
	float roadDistance;
	float walkingDistance;
	float f;

	bool operator>(const bestPath& other) const {
		return f > other.f;
	}
};