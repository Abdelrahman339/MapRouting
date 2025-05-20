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

double calculateEuclideanDistance(int startPointId, int goalPointId, const vector <coordinates>& Nodes);
double calculateRoadTime(double distance, double speed); //for each road
double calculateWalkingTime(double distance);//called twice (1st time => to reach start point , 2nd time => to reach end point)

double meterToKilometer(double meter);
double minuteToHours(double minutes);
int addNode(unordered_map<int, vector<edge>>& graph, const vector<pair<int, double>>& points);
void addNode( vector <coordinates>& coordinate, coordinates coor);

double roundUp(double number);