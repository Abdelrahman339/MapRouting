#pragma once
#include <vector>
#include "../graph/coordinates.h"
#include <unordered_map>

float calculateEuclideanDistance(float x1, float y1, float x2, float y2);


//Radius is given by meters
//(x,y) => (where user is standing / destination endpoint) => called twice
vector<int> getNodesWithinRadius(float targetX, float targetY, float radius, unordered_map<int, coordinates>& Nodes);
float calculateTime(float distance, float speed); //for each road


float kilometerToMeter(float kilo);
float meterToKilometer(float meter);

float hoursToMinutes(float hours);
float minuteToHours(float minutes);

