#include "helperFunctions.h"


using namespace std;


const float walkingSpeed = 5.0f; //  5km/hr

float calculateEuclideanDistance(float startPointId,float endPointId, unordered_map<int, coordinates>& Nodes) {
    coordinates startPointcoor = Nodes[startPointId];
    coordinates endPointcoor = Nodes[endPointId];
    float X = (endPointcoor.getX_coordinate() - startPointcoor.getX_coordinate());
    float Y = (endPointcoor.getY_coordinate() - startPointcoor.getY_coordinate());

    return sqrt(X + Y);
}

vector<pair<int,int>> getNodesWithinRadius(float targetX, float targetY, float radius, unordered_map<int, coordinates>& Nodes) {

    vector<pair<int,int>> result;

    //iterate over all nodes => N-1
    //for now O(Nodes) , may be changed later

    for (const auto& pair : Nodes) {
        int nodeId = pair.first;
        coordinates coord = pair.second;
        float nodeX = coord.getX_coordinate();
        float nodeY = coord.getY_coordinate();
        float distance = calculateEuclideanDistance(targetX, targetY, nodeX, nodeY);
        if (distance <= radius) 
            result.push_back(make_pair(nodeId,distance));
        if (distance < 0.002) break;
        
    }
}


float calculateRoadTime(float distance, float speed) {
    return (distance / speed);
}

float calculateWalkingTime(float distance) {
    float walkSpeedInMeterPerMin = ((walkingSpeed * 1000) / 60);
    return distance/walkSpeedInMeterPerMin;

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




