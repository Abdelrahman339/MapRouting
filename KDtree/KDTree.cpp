#include "KDTree.h"
#include <algorithm>

KDNode* KDTree::build(vector<pair<int, coordinates>>& points, int depth) {
    if (points.empty()) return nullptr;

    int axis = depth % 2;
    sort(points.begin(), points.end(), [axis](auto& a, auto& b) {
        return axis == 0 ? a.second.x_coordinate < b.second.x_coordinate
            : a.second.y_coordinate < b.second.y_coordinate;
        });

    int mid = points.size() / 2;
    KDNode* node = new KDNode{ points[mid].first, points[mid].second };

    vector<pair<int, coordinates>> left(points.begin(), points.begin() + mid);
    vector<pair<int, coordinates>> right(points.begin() + mid + 1, points.end());

    node->left = build(left, depth + 1);
    node->right = build(right, depth + 1);

    return node;
}

void KDTree::radiusSearch(KDNode* node, float x, float y, float radiusSquared, unordered_map<int, float>& result, int depth) {
    if (!node) return;

    float dx = node->point.x_coordinate - x;
    float dy = node->point.y_coordinate - y;
    float distSq = dx * dx + dy * dy;

    if (distSq <= radiusSquared) {
        result[node->nodeId] = sqrt(distSq);
    }

    int axis = depth % 2;
    float delta = (axis == 0) ? dx : dy;
    float deltaSq = delta * delta;

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

void KDTree::buildTree(const unordered_map<int, coordinates>& nodes) {
    vector<pair<int, coordinates>> points;
    for (const auto& [id, coord] : nodes) {
        points.emplace_back(id, coord);
    }
    root = build(points, 0);
}

unordered_map<int, float> KDTree::queryRadius(float x, float y, float radius) {
    unordered_map<int, float> result;
    radiusSearch(root, x, y, radius * radius, result, 0);
    return result;
}
