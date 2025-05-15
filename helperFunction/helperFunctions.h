#pragma once
#include <vector>
#include "../graph/edge.h"
#include "../graph/coordinates.h"
#include <unordered_map>
#include <queue>
#include "../A_Star/A_Star.h"
#include <cmath>
#include <math.h>
#include <utility>
#include <sstream>
#include <iomanip>

const float walkingSpeed = 5.0f; //  5km/hr

float calculateEuclideanDistance(int startPointId, int goalPointId, unordered_map<int, coordinates> Nodes);
float calculateEuclideanDistance(int startPointId, float destx, float destY, unordered_map<int, coordinates> Nodes);


//Radius is given by meters
//(x,y) => (where user is standing / destination endpoint) => called twice
unordered_map<int, float> getNodesWithinRadius(float targetX, float targetY, float radius, unordered_map<int, coordinates> Nodes);
float calculateRoadTime(float distance, float speed); //for each road
float calculateWalkingTime(float distance);//called twice (1st time => to reach start point , 2nd time => to reach end point)
unordered_map<int, float> getNodesWithinRadiusGrid(float targetX,float targetY,float radius,unordered_map<int, coordinates>& Nodes,unordered_map<string, vector<int>>& spatialGrid,float cellSize);

float kilometerToMeter(float kilo);
float meterToKilometer(float meter);
float hoursToMinutes(float hours);
float minuteToHours(float minutes);
float truncateTwoDecimals(float value);

int addNode(unordered_map<int, vector<edge>>& graph, unordered_map<int, float>);
void addNode(unordered_map<int, coordinates>& coordinate, coordinates coor);

