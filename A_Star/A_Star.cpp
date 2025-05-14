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


float A_Star::calcG(int startN, edge endN, float prevG) {

	float roadTime = calculateRoadTime(endN.edgeLength, endN.edgeSpeed);
	roadTime = hoursToMinutes(roadTime);
	float time = prevG + roadTime;
	return time;


};

bestPath A_Star::A(unordered_map<int, vector<edge>> graph, int sourcePointID, int destinationPointID,float maxSpeed,float R, unordered_map<int, coordinates>coordinate)
{
	priority_queue<NodeInfo, vector<NodeInfo>, greater<NodeInfo>> priorityQ;
	priorityQ.push({ sourcePointID, 0 });
	
	bestPath result;

	unordered_map<int, int> thePath;
	unordered_set<int> visited;
	unordered_map<int, float> gCosts;
	
	
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
		
		int currentnodeId = priorityQ.top().node;
		priorityQ.pop();
		if (currentnodeId == destinationPointID)
		{
			vector<int> path;
	
			for (int node = thePath[destinationPointID]; node != sourcePointID; node = thePath[node])
				result.nodes.push(node);
			
			//p.nodes.insert();
			result.walkingDistance = walkDistances[currentnodeId];
			result.roadDistance = roadDistances[currentnodeId];
			result.totalDistance = result.walkingDistance + result.roadDistance;
			float roadInMinutes= hoursToMinutes(roadTime[currentnodeId]);
			float walkingInMinutes = walkTime[currentnodeId];
			result.time = walkingInMinutes + roadInMinutes;
			return result;
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
