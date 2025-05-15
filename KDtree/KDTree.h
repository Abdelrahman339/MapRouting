#pragma once
#include "../File/File.h"
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

struct KDNode {
	int nodeId;
	coordinates point;
	KDNode* left = nullptr;
	KDNode* right = nullptr;
};

class KDTree {

public:
	KDNode* root;
	const vector<coordinates>* coordsRef;

	KDNode* build(vector < int > &points, int depth);
	
	void radiusSearch(
		KDNode* node,
		double x1, double y1,
		double x2, double y2,
		double radiusSquared,
		vector<std::pair<int, double>>& startPoints,
		vector<std::pair<int, double>>& endPoints,int depth);
	KDTree() : root(nullptr) {}
	
	void buildTree(const vector<coordinates>& coords);
	void queryRadius(
		double x1, double y1,
		double x2, double y2,
		double radius,
		unordered_map<int, double>& startPoints,
		unordered_map<int, double>& endPoints);
};
