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

void KDTree::radiusSearch(
    KDNode* node,
    double x1, double y1,
    double x2, double y2,
    double radiusSquared,
    std::vector<std::pair<int, double>>& startPoints,
    std::vector<std::pair<int, double>>& endPoints,
    int depth)
{
    if (!node) return;

    const auto& pt = node->point;

    // Compute squared distances only once
    double dx1 = pt.x_coordinate - x1;
    double dy1 = pt.y_coordinate - y1;
    double distSq1 = dx1 * dx1 + dy1 * dy1;

    double dx2 = pt.x_coordinate - x2;
    double dy2 = pt.y_coordinate - y2;
    double distSq2 = dx2 * dx2 + dy2 * dy2;

    if (distSq1 <= radiusSquared) {
        startPoints.emplace_back(node->nodeId, sqrt(distSq1));
    }
    if (distSq2 <= radiusSquared) {
        endPoints.emplace_back(node->nodeId, sqrt(distSq2));
    }

    int axis = depth % 2;
    double coord = (axis == 0) ? pt.x_coordinate : pt.y_coordinate;
    double t1 = (axis == 0) ? x1 : y1;
    double t2 = (axis == 0) ? x2 : y2;

    bool goLeft = false, goRight = false;

    // Check pruning conditions separately for each target
    if ((coord - t1) * (coord - t1) <= radiusSquared ||
        (coord - t2) * (coord - t2) <= radiusSquared) {
        goLeft = goRight = true;
    }
    else {
        double radius = std::sqrt(radiusSquared);
        if (coord > t1 + radius && coord > t2 + radius) {
            goLeft = true;
        }
        else if (coord < t1 - radius && coord < t2 - radius) {
            goRight = true;
        }
        else {
            goLeft = goRight = true;
        }
    }

    if (goLeft)
        radiusSearch(node->left, x1, y1, x2, y2, radiusSquared, startPoints, endPoints, depth + 1);
    if (goRight)
        radiusSearch(node->right, x1, y1, x2, y2, radiusSquared, startPoints, endPoints, depth + 1);
}



void KDTree::buildTree(const std::vector<coordinates>& coords) {
    this->coordsRef = &coords;

    int N = coords.size();
    vector<int> indices(N);
    for (int i = 0; i < N; ++i) indices[i] = i;

    root = build(indices, 0);
}

void KDTree::queryRadius(
    double x1, double y1,
    double x2, double y2,
    double radius,
    std::unordered_map<int, double>& startPoints,
    std::unordered_map<int, double>& endPoints)
{
    //double radiusSquared = radius * radius;
    //radiusSearch(root, x1, y1, x2, y2, radiusSquared, startPoints, endPoints, 0);
}