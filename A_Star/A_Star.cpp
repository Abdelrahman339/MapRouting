#include "A_Star.h"





float A_Star::calcF(float h, float g) {};
float A_Star::calch(float n, coordinates destenation, unordered_map<int, coordinates> coordinate) {};
float A_Star::calcg(float startN, edge endN, float prevG) {};

vector<int> A_Star::findPath(vector<pair<int, int>> startPoints, vector<float> endPoints, coordinates DestPoint, unordered_map<int, vector<edge>> graph, unordered_map<int, coordinates> coordinate)
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
		h = calch(pointId, DestPoint, coordinate);
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
				h = calch(pointId, DestPoint, coordinate);
				f = calcF(h, g);
				bestPathQ.push(make_pair(neighbor.node, f));
			}
		}
	}
};