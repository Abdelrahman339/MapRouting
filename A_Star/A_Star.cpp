#include "A_Star.h"
#include <functional>





float A_Star::calcF(float h, float g) {
	return h + g;
};

float A_Star::calcH(int startPointID, int destinationPointId, unordered_map<int, coordinates> coordinate, float maxSpeed, float R) {
	float distance = calculateEuclideanDistance(startPointID, destinationPointId, coordinate);
	if (distance < R)
		return hoursToMinutes(distance / walkingSpeed);
	float carTime = hoursToMinutes((distance - R) / maxSpeed);
	float walkTime = hoursToMinutes(R / walkingSpeed);
	float totalTime = carTime + walkTime;
	return totalTime;

};

float A_Star::calcHForEndpoint(int nodeId, const unordered_map<int, float>& endPoints,const unordered_map<int, coordinates>& coordinate,float maxSpeed, float R) {
	float minH = numeric_limits<float>::max();

	for (const auto& [endId, _] : endPoints) {
		float distance = calculateEuclideanDistance(nodeId,coordinate.at(endId).x_coordinate,coordinate.at(endId).y_coordinate,coordinate);
		float currentH;
		if (distance < R) {
			currentH = hoursToMinutes(distance / walkingSpeed);
		}
		else {
			float carTime = hoursToMinutes((distance - R) / maxSpeed);
			float walkTime = hoursToMinutes(R / walkingSpeed);
			currentH = carTime + walkTime;
		}

		if (currentH < minH) {
			minH = currentH;
		}
	}

	return minH;
}

float A_Star::calcG(int startN, edge endN, float prevG) {

	float roadTime = calculateRoadTime(endN.edgeLength, endN.edgeSpeed);
	roadTime = hoursToMinutes(roadTime);
	float time = prevG + roadTime;
	return time;


};

//bestPath A_Star::findPath(unordered_map<int, float> startPoints, unordered_map<int, float> endPoints, coordinates DestPoint, unordered_map<int, vector<edge>> graph, unordered_map<int, coordinates> coordinate, float maxSpeed, vector<query> qu)
//{
//
//	query q = qu[0];
//
//	priority_queue<bestPath, vector<bestPath>, greater<bestPath>> bestPathes;
//	unordered_map<int, float>prevGs;
//	unordered_set<int>visitedNodes;
//
//	unordered_map<int, float> prevRoadDistances;
//	unordered_map<int, float> prevWalkDistances;
//	unordered_map<int, float> prevRoadTime;
//
//	// Min-heap priority_queue to sort paths by cost (float)
//	function<bool(pair<int, float>, pair<int, float>)> cmp = [](pair<int, float> a, pair<int, float> b) {
//		return a.second > b.second;
//		};
//
//	priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(cmp)> bestPathQ(cmp);
//	float f, g, h, prevG;
//	int counter = 0;
//	g = 0;
//	int pointId;
//
//	vector<int> best;
//	for (auto& [startPointId, distance] : startPoints)
//	{
//		bestPath path;
//		//g,f,h for starting points
//		pointId = startPointId;
//		g = calculateWalkingTime(kilometerToMeter(distance));
//		h = calcH(pointId, DestPoint, coordinate, maxSpeed, q.R);
//		f = calcF(h, g);
//
//		//TOTAL DISTANCE AND TIME CALCULATIONS
//		prevWalkDistances[startPointId] = distance;
//		prevRoadTime[startPointId] = 0;
//		prevRoadDistances[startPointId] = 0;
//
//
//		bestPathQ.push(make_pair(pointId, f));
//		prevGs[pointId] = g;
//		path.startNodeId = startPointId;
//		visitedNodes.insert(startPointId);
//
//		while (true)
//		{
//			pointId = bestPathQ.top().first;
//			path.nodes.insert(pointId);
//			path.f = f;
//			prevG = prevGs[pointId];
//
//			if (endPoints.find(pointId) == endPoints.end())
//				bestPathQ = priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(cmp)>(cmp);
//
//			vector<edge> neighbors;
//			neighbors = graph[pointId];
//			if (neighbors.empty())
//				break;
//			for (edge neighbor : neighbors)
//			{
//				float newRoadDist = prevRoadDistances[pointId] + neighbor.edgeLength;
//				float newWalkDist = prevWalkDistances[pointId];
//				float newRoadTime = prevRoadTime[pointId] + calculateRoadTime(neighbor.edgeLength, neighbor.edgeSpeed);
//
//
//
//				if (endPoints.find(pointId) != endPoints.end() && endPoints.find(neighbor.node) == endPoints.end())
//				{
//					counter++;
//					continue;
//				}
//				if (visitedNodes.find(neighbor.node) != visitedNodes.end()) {
//					counter++;
//					continue;
//				}
//				visitedNodes.insert(neighbor.node);
//				g = calcG(pointId, neighbor, prevG);
//				h = calcH(neighbor.node, DestPoint, coordinate, maxSpeed, q.R);
//				f = calcF(h, g);
//				bestPathQ.push(make_pair(neighbor.node, f));
//				prevGs[neighbor.node] = g;
//
//				prevRoadDistances[neighbor.node] = newRoadDist;
//				prevWalkDistances[neighbor.node] = newWalkDist;
//				prevRoadTime[neighbor.node] = newRoadTime;
//			}
//
//			if (endPoints.count(pointId)) {
//				path.roadDistance = prevRoadDistances[pointId];
//				path.walkingDistance = prevWalkDistances[pointId] + (endPoints[pointId]);
//				float walkingTime = hoursToMinutes(prevWalkDistances[pointId] / 5 + (endPoints[pointId]) / 5);
//				float roadTime = hoursToMinutes(prevRoadTime[pointId]);
//				path.time = walkingTime + roadTime;
//			}
//
//			if (counter == neighbors.size())
//				break;
//			counter = 0;
//		}
//
//		bestPathes.push(path);
//		visitedNodes.clear();
//		prevGs.clear();
//		bestPathQ = priority_queue<pair<int, float>, vector<pair<int, float>>, decltype(cmp)>(cmp);
//		counter = 0;
//	}
//	return bestPathes.top();
//};







vector<int> A_Star::A(unordered_map<int, vector<edge>> graph, int sourcePointID, int destinationPointID,float maxSpeed,float R, unordered_map<int, coordinates>coordinate)
{
	priority_queue<NodeInfo, vector<NodeInfo>, greater<NodeInfo>> priorityQ;
	priorityQ.push({ sourcePointID, 0 });
	

	unordered_map<int, int> thePath;
	set<int> visited;
	unordered_map<int, float> gCosts;
	//Other Ouput Calculations
	
	unordered_map<int, float> walkDistances;
	unordered_map<int, float> roadDistances;
	unordered_map<int, float> walkTime;
	unordered_map<int, float> roadTime;

	
	walkDistances[sourcePointID] = 0;
	roadDistances[sourcePointID] = 0;
	roadTime[sourcePointID] = 0;
	walkTime[sourcePointID] = 0;

	gCosts[sourcePointID] = 0;

	while (!priorityQ.empty())
	{
		bestPath p;
		int currentnodeId = priorityQ.top().node;
		priorityQ.pop();
		if (currentnodeId == destinationPointID)
		{
			vector<int> path;
	
			for (int node = destinationPointID; node != sourcePointID; node = thePath[node])
				path.push_back(node);
			path.push_back(sourcePointID);
			reverse(path.begin(), path.end());
			
			p.walkingDistance = walkDistances[currentnodeId];
			p.roadDistance = roadDistances[currentnodeId];
			float roadInMinutes= hoursToMinutes(roadTime[currentnodeId]);
			float walkingInMinutes = walkTime[currentnodeId];
			p.time = walkingInMinutes + roadInMinutes;
			return path;
		}

		if (visited.count(currentnodeId))
			continue;
		visited.insert(currentnodeId);

		vector<edge> neighbors = graph[currentnodeId];

		

		for (edge neighbor : neighbors)
		{
			//calc the g , h and f for each neighbor 
			float tempG = calcG(currentnodeId, neighbor, gCosts[currentnodeId]);

			if (!gCosts.count(neighbor.node) || tempG < gCosts[neighbor.node])
			{
				
				thePath[neighbor.node] = currentnodeId;
				gCosts[neighbor.node] = tempG;
				


				
				if (currentnodeId == sourcePointID) {
					walkDistances[neighbor.node] = neighbor.edgeLength;
					walkTime[neighbor.node] = walkTime[currentnodeId] + calculateWalkingTime(kilometerToMeter(neighbor.edgeLength));
				}
				else if (neighbor.node == destinationPointID) {
					walkDistances[neighbor.node] = walkDistances[currentnodeId] + neighbor.edgeLength;	
					walkTime[neighbor.node] = walkTime[currentnodeId] + calculateWalkingTime(kilometerToMeter(neighbor.edgeLength));
				}
				else {
					walkDistances[neighbor.node] = walkDistances[currentnodeId];
					walkTime[neighbor.node] = walkTime[currentnodeId];
				}

				if (currentnodeId != sourcePointID && neighbor.node != destinationPointID) {
					roadDistances[neighbor.node] = roadDistances[currentnodeId] + neighbor.edgeLength;
					roadTime[neighbor.node] = roadTime[currentnodeId] + calculateRoadTime(neighbor.edgeLength, neighbor.edgeSpeed);
				}
				else {
					roadDistances[neighbor.node] = roadDistances[currentnodeId];
					roadTime[neighbor.node] = roadTime[currentnodeId];
				}

				float H = calcH(sourcePointID,destinationPointID, coordinate,maxSpeed,R);
				float F = calcF(H, tempG);
				priorityQ.push({ neighbor.node,F });
				
			}

		}
	}
};
