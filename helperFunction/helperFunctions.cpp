#include "helperFunctions.h"
#include <cmath>

using namespace std;


const float walkingSpeed = 5.0f; //  5km/hr

float calculateEuclideanDistance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

vector<int> getNodesWithinRadius(float targetX, float targetY, float radius, unordered_map<int, coordinates>& Nodes) {

    vector<int> result;

    //iterate over all nodes => N-1
    //for now O(Nodes) , may be changed later

    for (const auto& pair : Nodes) {
        int nodeId = pair.first;
        coordinates coord = pair.second;
        float nodeX = coord.getX_coordinate();
        float nodeY = coord.getY_coordinate();
        float distance = calculateEuclideanDistance(targetX, targetY, nodeX, nodeY);
        if (distance <= radius) 
            result.push_back(nodeId);
        
    }
}


float calculateTime(float distance, float speed) {
    return distance / speed;
}

//For distances
float kilometerToMeter(float kilo) {
    return kilo*1000.0f;
}

float meterToKilometer(float meter) {
    return meter / 1000.0f;
}

//for time
float hoursToMinutes(float hours) {
    return hours * 60.0f;
}

float minuteToHours(float minutes) {
    return minutes / 60.0f;
}

//vector<int> getNodesWithinRadius(, float x, float y, float radius) {
//    vector<int> result;
//    for () {
//        
//        
//        float distance = calculateEuclideanDistance(targetX, targetY, node.x, node.y);
//        if (distance <= radius) {
//            result.push_back(node.id);
//        }
//    return result;
//}


