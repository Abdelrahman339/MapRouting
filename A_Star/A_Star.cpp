#include "A_Star.h"





float A_Star::calcF(float h, float g) {
	return h + g;
};

float A_Star::calch(float n, coordinates destination, unordered_map<int, coordinates> coordinate,float maxSpeed,float R) {
	float distance = calculateEuclideanDistance(n, destination.getX_coordinate(), destination.getY_coordinate(), coordinate);
	float carTime = hoursToMinutes((distance - R) / maxSpeed);
	float walkingTime = hoursToMinutes(meterToKilometer(R) / walkingTime);
	return carTime + walkingTime;

};

float A_Star::calcg(float startN, edge endN, float prevG) {
	
	float roadTime = calculateRoadTime(endN.edgeLength, endN.edgeSpeed);
	float time=hoursToMinutes(prevG + roadTime);
	return time;

		
};

vector<int> A_Star::findPath(vector<pair<int, int>> startPoints, vector<float> endPoints, coordinates DestPoint, unordered_map<int, vector<edge>> graph, unordered_map<int, coordinates> coordinate,float maxSpeed,query q)
{

	vector <pair<int,vector<int>>> bestPaths;
	priority_queue<pair<int, float>,greater<float>> bestPathQ;
	float f, g, h;
	g = 0;
	int pointId;
	for (auto& [startPointId, distance] : startPoints)
	{
		//g,f,h for starting points
		pointId = startPointId;
		g = calculateWalkingTime(distance);
		h = calch(pointId, DestPoint, coordinate,maxSpeed,q.R);
		f = calcF(h, g);
		bestPathQ.push(make_pair(pointId,f));
		while (true)
		{
			pointId = bestPathQ.top();
			bestPathQ.pop();
			vector<edge> neighbors;
			neighbors = graph[pointId];
			if (neighbors.empty()) break;
			for (edge neighbor : neighbors)
			{	
				g = calcg(pointId, neighbor, g);
				h = calch(pointId, DestPoint, coordinate, maxSpeed, q.R);
				f = calcF(h, g);
				bestPathQ.push(make_pair(neighbor.node, f));
			}
		}
	}
};