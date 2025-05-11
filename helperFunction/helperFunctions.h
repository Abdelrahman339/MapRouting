#pragma once
#include <vector>
#include "../graph/coordinates.h"
#include <unordered_map>
#include <cmath>
#include <math.h>
#include <utility>

const float walkingSpeed = 5.0f; //  5km/hr

float calculateEuclideanDistance(float startPointId, float endPointX, float endPointY, unordered_map<int, coordinates>& Nodes);


//Radius is given by meters
//(x,y) => (where user is standing / destination endpoint) => called twice
unordered_map<int, float> getNodesWithinRadius(float targetX, float targetY, float radius, unordered_map<int, coordinates>& Nodes);
float calculateRoadTime(float distance, float speed); //for each road
float calculateWalkingTime(float distance);//called twice (1st time => to reach start point , 2nd time => to reach end point)


float kilometerToMeter(float kilo);
float meterToKilometer(float meter);
float hoursToMinutes(float hours);
float minuteToHours(float minutes);
float truncateTwoDecimals(float value);

