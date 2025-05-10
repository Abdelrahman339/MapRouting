#include "A_Star.h"





float A_Star::calcF(float h, float g) {
	return h + g;
};

float A_Star::calcH(int n, coordinates destination, unordered_map<int, coordinates> coordinate,float maxSpeed,float R) {
	float distance = calculateEuclideanDistance(n, destination.getX_coordinate(), destination.getY_coordinate(), coordinate);
	float carTime = hoursToMinutes((distance - meterToKilometer(R) )/ maxSpeed);
	float walkTime = hoursToMinutes(meterToKilometer(R) / walkingSpeed);
	return carTime + walkTime;

};

float A_Star::calcG(int startN, edge endN, float prevG) {
	
	float roadTime = calculateRoadTime(endN.edgeLength, endN.edgeSpeed);
	roadTime = hoursToMinutes(roadTime);
	float time = prevG + roadTime;
	return time;

		
};

vector<int> A_Star::findPath(vector<pair<int, float>> startPoints, vector<pair<int, float>> endPoints, coordinates DestPoint, unordered_map<int, vector<edge>> graph, unordered_map<int, coordinates> coordinate,float maxSpeed,vector<query> qu)
{
	query q = qu[0];
	unordered_map<int, vector<int>> bestPaths;
	unordered_map<int, float>prevGs;
	// Min-heap priority_queue to sort paths by cost (float)
	auto cmp = [](const pair<int, float>& a, const pair<int, float>& b) {
		return a.second > b.second;
		};
	priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(cmp)> bestPathQ(cmp);
	float f, g, h,prevG;
	g = 0;
	int pointId;
	for (auto& [startPointId, distance] : startPoints)
	{
		//g,f,h for starting points
		pointId = startPointId;
		g = calculateWalkingTime(kilometerToMeter(distance));
		h = calcH(pointId, DestPoint, coordinate,maxSpeed,q.R);
		f = calcF(h, g);
		bestPathQ.push(make_pair(pointId,f));
		prevGs[pointId] = g;
		while (true)
		{
			pointId = bestPathQ.top().first;
			bestPaths[startPointId].push_back(pointId);
			prevG=prevGs[pointId];
			bestPathQ.pop();

			vector<edge> neighbors;
			neighbors = graph[pointId];

			if (neighbors.empty()) break;
			for (edge neighbor : neighbors)
			{	
				g = calcG(pointId, neighbor, g);
				h = calcH(pointId, DestPoint, coordinate, maxSpeed, q.R);
				f = calcF(h, g);
				bestPathQ.push(make_pair(neighbor.node, f));
				prevGs[neighbor.node] = g;
			}
		}
	}
	vector<int> best;
	return best;
};