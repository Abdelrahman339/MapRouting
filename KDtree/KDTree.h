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
private:
    KDNode* root;

    KDNode* build(vector<pair<int, coordinates>>& points, int depth);
    void radiusSearch(KDNode* node, double x, double y, double radiusSquared, unordered_map<int, double>& result, int depth);

public:
    KDTree() : root(nullptr) {}
    void buildTree(const unordered_map<int, coordinates>& nodes);
    unordered_map<int, double> queryRadius(double x, double y, double radius);
};
