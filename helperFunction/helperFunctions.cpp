#include "helperFunctions.h"
#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

// Calculates Euclidean distance between two node IDs [O(1)]
double calculateEuclideanDistance(int startPointId, int goalPointId, const vector<coordinates>& Nodes) {
    double startX = Nodes[startPointId].x_coordinate; // O(1)
    double startY = Nodes[startPointId].y_coordinate; // O(1)
    double goalX = Nodes[goalPointId].x_coordinate;   // O(1)
    double goalY = Nodes[goalPointId].y_coordinate;   // O(1)

    double dx = goalX - startX;
    double dy = goalY - startY;

    return sqrt(dx * dx + dy * dy); // O(1)
}



// Calculates time (in minutes) to travel a distance with a given speed (km/min) [O(1)]
double calculateRoadTime(double distance, double speed) {
    return distance / speed; // O(1)
}

// Calculates walking time in minutes assuming fixed speed [O(1)]
double calculateWalkingTime(double distance) {
    double walkSpeedInMetersPerMinute = (walkingSpeed * 1000.0) / 60.0; // O(1)
    return distance / walkSpeedInMetersPerMinute; // O(1)
}

// Converts meters to kilometers [O(1)]
double meterToKilometer(double meter) {
    return meter / 1000.0; // O(1)
}

// Converts minutes to hours [O(1)]
double minuteToHours(double minutes) {
    return minutes / 60.0; // O(1)
}

double HoursToMinutes(double hours) {
    return hours * 60;
}

// Adds a new node with edges to the graph, connecting to provided points [O(k)], where k = points.size()
int addNode(unordered_map<int, vector<edge>>& graph, const vector<pair<int, double>>& points) {
    int nodeId = graph.size(); // O(1)

    for (const auto& [pointID, distance] : points) { // O(k)
        edge e;
        e.node = pointID;
        e.edgeSpeed = 5;

        // Initialize edgeSpeeds with same size as graph[0][0].edgeSpeeds
        for (int i = 0; i < graph[0][0].edgeSpeeds.size(); i++) { // O(m), m = edgeSpeeds.size()
            e.edgeSpeeds.push_back(5);
        }

        e.edgeLength = distance;
        e.cost = 5 / distance;

        graph[nodeId].push_back(e); // O(1)

        // Add reverse edge
        e.node = nodeId;
        graph[pointID].push_back(e); // O(1)
    }

    return nodeId;
}

// Adds coordinate to coordinates vector [O(1)]
void addNode(vector<coordinates>& coordinate, coordinates coor) {
    coordinate.push_back(coor); // O(1)
}

// Rounds a number to 2 decimal places [O(1)]
double roundUp(double number) {
    return round(number * 100.0) / 100.0; // O(1)
}
