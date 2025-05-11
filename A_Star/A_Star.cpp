#include "A_Star.h"
#include <functional>





float A_Star::calcF(float h, float g) {
	return h + g;
};

float A_Star::calcH(int n, coordinates destination, unordered_map<int, coordinates> coordinate, float maxSpeed, float R) {
	float distance = calculateEuclideanDistance(n, destination.x_coordinate, destination.y_coordinate, coordinate);
	if (distance < R)
		return hoursToMinutes(distance / walkingSpeed);
	float carTime = hoursToMinutes((distance - R) / maxSpeed);
	float walkTime = hoursToMinutes(R / walkingSpeed);
	float totalTime = carTime + walkTime;
	return totalTime;

};

float A_Star::calcG(int startN, edge endN, float prevG) {

	float roadTime = calculateRoadTime(endN.edgeLength, endN.edgeSpeed);
	roadTime = hoursToMinutes(roadTime);
	float time = prevG + roadTime;
	return time;


};

bestPath A_Star::findPath(unordered_map<int, float> startPoints, unordered_map<int, float> endPoints, coordinates DestPoint, unordered_map<int, vector<edge>> graph, unordered_map<int, coordinates> coordinate, float maxSpeed, vector<query> qu)
{

	query q = qu[7];
	//for (int i = 0; i < q.NumOfQueries; i++) {};

	priority_queue<bestPath, vector<bestPath>, greater<bestPath>> bestPathes;
	unordered_map<int, float>prevGs;
	unordered_set<int>visitedNodes;


	// Min-heap priority_queue to sort paths by cost (float)
	function<bool(pair<int, float>, pair<int, float>)> cmp = [](pair<int, float> a, pair<int, float> b) {
		return a.second > b.second;
		};
	priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(cmp)> bestPathQ(cmp);
	float f, g, h, prevG;
	int counter = 0;
	g = 0;
	int pointId;
	vector<int> best;
	for (auto& [startPointId, distance] : startPoints)
	{
		bestPath path;
		//g,f,h for starting points
		pointId = startPointId;
		g = calculateWalkingTime(kilometerToMeter(distance));
		h = calcH(pointId, DestPoint, coordinate, maxSpeed, q.R);
		f = calcF(h, g);
		bestPathQ.push(make_pair(pointId, f));
		prevGs[pointId] = g;
		path.startNodeId = startPointId;
		visitedNodes.insert(startPointId);
		while (true)
		{
			pointId = bestPathQ.top().first;
			path.nodes.insert(pointId);
			path.f = f;
			prevG = prevGs[pointId];
			if (endPoints.find(pointId) == endPoints.end())
				bestPathQ = priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(cmp)>(cmp);
			
			vector<edge> neighbors;
			neighbors = graph[pointId];
			if (neighbors.empty())
				break;
			for (edge neighbor : neighbors)
			{
				if (endPoints.find(pointId) != endPoints.end() && endPoints.find(neighbor.node) == endPoints.end())
				{
					counter++;
					continue;
				}
				if (visitedNodes.find(neighbor.node) != visitedNodes.end()) {
					counter++;
					continue;
				}
				visitedNodes.insert(neighbor.node);
				g = calcG(pointId, neighbor, prevG);
				h = calcH(neighbor.node, DestPoint, coordinate, maxSpeed, q.R);
				f = calcF(h, g);
				bestPathQ.push(make_pair(neighbor.node, f));
				prevGs[neighbor.node] = g;
			}
			if (counter == neighbors.size())
				break;
			counter = 0;
		}

		bestPathes.push(path);
		visitedNodes.clear();
		prevGs.clear();
		bestPathQ = priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(cmp)>(cmp);
		counter = 0;
	}
	return bestPathes.top();
};