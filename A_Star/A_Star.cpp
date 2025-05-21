#include "A_Star.h"
#include <functional>

// ---------- Heuristic and Cost Functions ----------

double A_Star::calcF(double h, double g) {
    return h + g; // O(1)
};

double A_Star::calcH(int startPointID, int destinationPointId, const vector<coordinates>& coordinate, double maxSpeed, double R) {
    double distance = calculateEuclideanDistance(startPointID, destinationPointId, coordinate); // O(1)
    if (distance < R)
        return HoursToMinutes((distance / walkingSpeed)); // O(1)
    double carTime = HoursToMinutes(((distance - R) / maxSpeed)); // O(1)
    double walkTime = HoursToMinutes((R / walkingSpeed));         // O(1)
    return carTime + walkTime; // O(1)
};

double A_Star::calcG(int startN, edge endN, double prevG, double index) {
    double roadTime = (endN.edgeLength / endN.edgeSpeeds[index]); // O(1)
    roadTime = 60 * (roadTime); // O(1)
    return prevG + roadTime; // O(1)
};

double A_Star::calcG(int startN, edge endN, double prevG) {
    double roadTime = (endN.edgeLength / endN.edgeSpeed); // O(1)
    roadTime = HoursToMinutes((roadTime)); // O(1)
    return prevG + roadTime; // O(1)
};

// ---------- Main A* Algorithm ----------

bestPath A_Star::A(const unordered_map<int, vector<edge>>& graph, int sourcePointID, int destinationPointID, double maxSpeed, double R, const vector<coordinates>& coordinate)
{
    priority_queue<NodeInfo, vector<NodeInfo>, greater<NodeInfo>> priorityQ;
    // {neighbor.node, F, WalkDist, RoadDist, WalkTime, RoadTime} 
    priorityQ.push({ sourcePointID, 0, 0, 0, 0, 0 }); // O(log N)

    bestPath result;
    unordered_map<int, int> thePath; // O(1) 
    unordered_set<int> visited; // O(1) 
    unordered_map<int, double> gCosts; // O(1)

    gCosts[sourcePointID] = 0; // O(1)

    double H = calcH(sourcePointID, destinationPointID, coordinate, maxSpeed, R); // O(1)

    while (!priorityQ.empty()) // O(N)
    {
        NodeInfo current = priorityQ.top(); // O(1)
        priorityQ.pop(); // O(log N)

        if (current.node == destinationPointID) // O(1)
        {
            vector<int> path;
            for (int node = thePath[destinationPointID]; node != sourcePointID; node = thePath[node]) // O(path length)
                result.nodes.push_front(node); // O(1) per push_front

            result.walkingDistance = current.walkDist;
            result.roadDistance = current.roadDist;
            result.totalDistance = roundUp(current.walkDist + current.roadDist); // O(1)
            result.time = roundUp(current.walkTime + current.roadTime * 60);     // O(1)
            return result;
        }

        auto temp = visited.find(current.node); // O(1)
        if (temp != visited.end())
            continue;
        visited.insert(current.node); // O(1)

        for (edge neighbor : graph.at(current.node)) // O(Neighbour)
        {
            double tempG = calcG(current.node, neighbor, gCosts[current.node]); // O(1)
            auto it = gCosts.find(neighbor.node); // O(1)

            //we haven't been to that node yet or there is a better way
            if (it == gCosts.end() || tempG < it->second) // O(1)
            {
                thePath[neighbor.node] = current.node; // O(1)
                gCosts[neighbor.node] = tempG;         // O(1)

                double newWalkDist = current.walkDist;
                double newRoadDist = current.roadDist;
                double newWalkTime = current.walkTime;
                double newRoadTime = current.roadTime;

                if (current.node == sourcePointID || neighbor.node == destinationPointID) {
                    newWalkDist += neighbor.edgeLength;
                    newWalkTime += (1000 * neighbor.edgeLength) / ((walkingSpeed * 1000) / 60); // O(1)
                }
                else {
                    newRoadDist += neighbor.edgeLength;
                    newRoadTime += neighbor.edgeLength / neighbor.edgeSpeed; // O(1)
                }

                double F = H + tempG; // O(1)
                priorityQ.push({ neighbor.node, F, newWalkDist, newRoadDist, newWalkTime, newRoadTime }); // O(log V)
            }
        }
    }
};




