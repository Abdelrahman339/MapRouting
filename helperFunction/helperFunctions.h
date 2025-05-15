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

const double walkingSpeed = 5.0f; //  5km/hr

double calculateEuclideanDistance(int startPointId, int goalPointId, unordered_map<int, coordinates> Nodes);
double calculateEuclideanDistance(int startPointId, double destx, double destY, unordered_map<int, coordinates> Nodes);


//Radius is given by meters
//(x,y) => (where user is standing / destination endpoint) => called twice
unordered_map<int, double> getNodesWithinRadius(double targetX, double targetY, double radius, unordered_map<int, coordinates> Nodes);
double calculateRoadTime(double distance, double speed); //for each road
double calculateWalkingTime(double distance);//called twice (1st time => to reach start point , 2nd time => to reach end point)
unordered_map<int, double> getNodesWithinRadiusGrid(double targetX,double targetY,double radius,unordered_map<int, coordinates>& Nodes,unordered_map<string, vector<int>>& spatialGrid,double cellSize);

double kilometerToMeter(double kilo);
double meterToKilometer(double meter);
double hoursToMinutes(double hours);
double minuteToHours(double minutes);
double truncateTwoDecimals(double value);

int addNode(unordered_map<int, vector<edge>>& graph, unordered_map<int, double>);
void addNode(unordered_map<int, coordinates>& coordinate, coordinates coor);

double roundUp(double number);