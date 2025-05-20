#include "KDTree.h"
#include <algorithm>
#include <cmath>

// Builds the KDTree recursively.
// Time complexity: O(N log N)
KDNode* KDTree::build(std::vector<int>& indices, int depth) {
    if (indices.empty()) return nullptr; // O(1)

    int axis = depth % 2; // O(1)

    // Sort indices based on axis (x or y). 
    // Time: O(N log N)
    std::sort(indices.begin(), indices.end(), [&](int a, int b) {
        return axis == 0 ?
            (*coordsRef)[a].x_coordinate < (*coordsRef)[b].x_coordinate :
            (*coordsRef)[a].y_coordinate < (*coordsRef)[b].y_coordinate;
        });

    int mid = indices.size() / 2; // O(1)
    int midId = indices[mid];     // O(1)

    // Create node for the median point. O(1)
    KDNode* node = new KDNode{ midId, (*coordsRef)[midId] };

    // Divide indices into left and right. O(N)
    std::vector<int> left(indices.begin(), indices.begin() + mid);
    std::vector<int> right(indices.begin() + mid + 1, indices.end());

    // Recursive calls (depth increases). O(log N) levels, each visiting O(N) total.
    node->left = build(left, depth + 1);
    node->right = build(right, depth + 1);

    return node;
}

// Performs radius search for two target points simultaneously.
// Worst-case time: O(N), average-case: O(sqrt(N) + k) where k = number of results.
void KDTree::radiusSearch(
    KDNode* node,
    double x1, double y1,
    double x2, double y2,
    double radiusSquared,
    std::vector<std::pair<int, double>>& startPoints,
    std::vector<std::pair<int, double>>& endPoints,
    int depth)
{
    if (!node) return; // O(1)

    const auto& pt = node->point; // O(1)

    // Compute squared distance to both target points. O(1)
    double dx1 = pt.x_coordinate - x1, dy1 = pt.y_coordinate - y1;
    double distSq1 = dx1 * dx1 + dy1 * dy1;

    double dx2 = pt.x_coordinate - x2, dy2 = pt.y_coordinate - y2;
    double distSq2 = dx2 * dx2 + dy2 * dy2;

    // If within radius, record result. O(1)
    if (distSq1 <= radiusSquared) {
        startPoints.emplace_back(node->nodeId, std::sqrt(distSq1)); // O(1)
    }
    if (distSq2 <= radiusSquared) {
        endPoints.emplace_back(node->nodeId, std::sqrt(distSq2));   // O(1)
    }

    int axis = depth % 2; // O(1)
    double coord = (axis == 0) ? pt.x_coordinate : pt.y_coordinate; // O(1)
    double t1 = (axis == 0) ? x1 : y1;
    double t2 = (axis == 0) ? x2 : y2;

    // Determine subtree traversal
    bool goLeft = false, goRight = false;

    // Check if either target could be close enough across the splitting plane. O(1)
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

    // Recurse into valid subtrees
    if (goLeft)
        radiusSearch(node->left, x1, y1, x2, y2, radiusSquared, startPoints, endPoints, depth + 1);
    if (goRight)
        radiusSearch(node->right, x1, y1, x2, y2, radiusSquared, startPoints, endPoints, depth + 1);
}

// Initializes KDTree with coordinates and builds the tree.
// Time complexity: O(N log N)
void KDTree::buildTree(const std::vector<coordinates>& coords) {
    coordsRef = &coords; // O(1)

    int N = coords.size(); // O(1)
    std::vector<int> indices(N); // O(N)
    for (int i = 0; i < N; ++i) indices[i] = i; // O(N)

    root = build(indices, 0); // O(N log N)
}

// Wrapper to call radiusSearch and fill unordered_maps.
// Time complexity: Same as radiusSearch: O(sqrt(N) + k) average, O(N) worst.
void KDTree::queryRadius(
    double x1, double y1,
    double x2, double y2,
    double radius,
    std::unordered_map<int, double>& startMap,
    std::unordered_map<int, double>& endMap)
{
    std::vector<std::pair<int, double>> startPoints, endPoints;

    double radiusSquared = radius * radius; // O(1)

    radiusSearch(root, x1, y1, x2, y2, radiusSquared, startPoints, endPoints, 0); // See above

    // Fill the unordered_maps. O(k) where k = # of results
    for (const auto& [id, dist] : startPoints)
        startMap[id] = dist;

    for (const auto& [id, dist] : endPoints)
        endMap[id] = dist;
}
