#pragma once
#include <vector>
#include "../graph/coordinates.h"
#include <unordered_map>
#include <cmath>
#include <math.h>
#include <utility>
float calculateEuclideanDistance(float x1, float y1, float x2, float y2);


//Radius is given by meters
//(x,y) => (where user is standing / destination endpoint) => called twice
vector<pair<int,int>> getNodesWithinRadius(float targetX, float targetY, float radius, unordered_map<int, coordinates>& Nodes);
float calculateRoadTime(float distance, float speed); //for each road
float calculateWalkingTime(float distance);//called twice (1st time => to reach start point , 2nd time => to reach end point)


float kilometerToMeter(float kilo);
float meterToKilometer(float meter);

float hoursToMinutes(float hours);
float minuteToHours(float minutes);

