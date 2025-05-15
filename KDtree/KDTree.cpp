#include "KDTree.h"
#include <algorithm>

KDNode* KDTree::build(vector<int>& indices, int depth) {
    if (indices.empty()) return nullptr;

    int axis = depth % 2;

    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return axis == 0 ?
            (*coordsRef)[a].x_coordinate < (*coordsRef)[b].x_coordinate :
            (*coordsRef)[a].y_coordinate < (*coordsRef)[b].y_coordinate;
        });

    int mid = indices.size() / 2;
    int midId = indices[mid];
    KDNode* node = new KDNode{ midId, (*coordsRef)[midId] };

    std::vector<int> left(indices.begin(), indices.begin() + mid);
    std::vector<int> right(indices.begin() + mid + 1, indices.end());

    node->left = build(left, depth + 1);
    node->right = build(right, depth + 1);

    return node;
}

void KDTree::radiusSearch(KDNode* node, double x, double y, double radiusSquared, unordered_map<int, double>& result, int depth) {
    if (!node) return;

    double dx = node->point.x_coordinate - x;
    double dy = node->point.y_coordinate - y;
    double distSq = dx * dx + dy * dy;

    if (distSq <= radiusSquared) {
        result[node->nodeId] = sqrt(distSq);
    }

    int axis = depth % 2;
    double delta = (axis == 0) ? dx : dy;
    double deltaSq = delta * delta;

    if (delta > 0) {
        radiusSearch(node->left, x, y, radiusSquared, result, depth + 1);
        if (deltaSq <= radiusSquared)
            radiusSearch(node->right, x, y, radiusSquared, result, depth + 1);
    }
    else {
        radiusSearch(node->right, x, y, radiusSquared, result, depth + 1);
        if (deltaSq <= radiusSquared)
            radiusSearch(node->left, x, y, radiusSquared, result, depth + 1);
    }
}

void KDTree::buildTree(const std::vector<coordinates>& coords) {
    this->coordsRef = &coords;

    int N = coords.size();
    vector<int> indices(N);
    for (int i = 0; i < N; ++i) indices[i] = i;

    root = build(indices, 0);
}

unordered_map<int, double> KDTree::queryRadius(double x, double y, double radius) {
    unordered_map<int, double> result;
    radiusSearch(root, x, y, radius * radius, result, 0);
    return result;
}
