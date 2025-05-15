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
    void radiusSearch(KDNode* node, float x, float y, float radiusSquared, unordered_map<int, float>& result, int depth);

public:
    KDTree() : root(nullptr) {}
    void buildTree(const unordered_map<int, coordinates>& nodes);
    unordered_map<int, float> queryRadius(float x, float y, float radius);
};
