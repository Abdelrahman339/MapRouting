#include "A_Star.h"
#include <functional>





double A_Star::calcF(double h, double g) {
	return h + g;
};

double A_Star::calcH(int startPointID, int destinationPointId, unordered_map<int, coordinates> coordinate, double maxSpeed, double R) {
	double distance = calculateEuclideanDistance(startPointID, destinationPointId, coordinate);
	if (distance < R)
		return 60 * (distance / walkingSpeed);
	double carTime = 60 * ((distance - R) / maxSpeed);
	double walkTime = 60 * (R / walkingSpeed);
	return carTime + walkTime;

};


double A_Star::calcG(int startN, edge endN, double prevG, double index) {

	double roadTime = (endN.edgeLength / endN.edgeSpeeds[index]);
	roadTime = 60 * (roadTime);
	return prevG + roadTime;

};

double A_Star::calcG(int startN, edge endN, double prevG) {

	double roadTime = (endN.edgeLength / endN.edgeSpeed);
	roadTime = 60 * (roadTime);
	return prevG + roadTime;


};

bestPath A_Star::A(const unordered_map<int, vector<edge>> &graph, int sourcePointID, int destinationPointID, double maxSpeed, double R, const unordered_map<int, coordinates>&coordinate)
{
	priority_queue<NodeInfo, vector<NodeInfo>, greater<NodeInfo>> priorityQ;
	priorityQ.push({ sourcePointID, 0 });

	bestPath result;

	unordered_map<int, int> thePath;
	unordered_set<int> visited;
	unordered_map<int, double> gCosts;


	unordered_map<int, double> walkDistances;
	unordered_map<int, double> roadDistances;
	unordered_map<int, double> walkTime;
	unordered_map<int, double> roadTime;


	walkDistances[sourcePointID] = 0;
	roadDistances[sourcePointID] = 0;
	roadTime[sourcePointID] = 0;
	walkTime[sourcePointID] = 0;

	gCosts[sourcePointID] = 0;

	double H = calcH(sourcePointID, destinationPointID, coordinate, maxSpeed, R);

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
			result.totalDistance = roundUp(result.walkingDistance + result.roadDistance);
			double roadInMinutes = 60 * (roadTime[currentnodeId]);
			double walkingInMinutes = walkTime[currentnodeId];
			result.time = roundUp(walkingInMinutes + roadInMinutes);
			return result;
		}
		auto temp = visited.find(currentnodeId);
		if (temp != visited.end())
			continue;
		visited.insert(currentnodeId);



		for (edge neighbor : graph.at(currentnodeId))
		{
			//calc the g , h and f for each neighbor 
			double tempG = calcG(currentnodeId, neighbor, gCosts[currentnodeId]);
			auto it = gCosts.find(neighbor.node);
			if (it == gCosts.end() || tempG < it->second)
			{

				thePath[neighbor.node] = currentnodeId;
				gCosts[neighbor.node] = tempG;




				if (currentnodeId == sourcePointID) {
					walkDistances[neighbor.node] = neighbor.edgeLength;
					walkTime[neighbor.node] = walkTime[currentnodeId] + (1000 * (neighbor.edgeLength)) / ((walkingSpeed * 1000) / 60);
				}
				else if (neighbor.node == destinationPointID) {
					walkDistances[neighbor.node] = walkDistances[currentnodeId] + neighbor.edgeLength;
					walkTime[neighbor.node] = walkTime[currentnodeId] + (1000 * (neighbor.edgeLength)) / ((walkingSpeed * 1000) / 60);
				}
				else {
					walkDistances[neighbor.node] = walkDistances[currentnodeId];
					walkTime[neighbor.node] = walkTime[currentnodeId];
				}

				if (currentnodeId != sourcePointID && neighbor.node != destinationPointID) {
					roadDistances[neighbor.node] = roadDistances[currentnodeId] + neighbor.edgeLength;
					roadTime[neighbor.node] = roadTime[currentnodeId] + neighbor.edgeLength / neighbor.edgeSpeed;
				}
				else {
					roadDistances[neighbor.node] = roadDistances[currentnodeId];
					roadTime[neighbor.node] = roadTime[currentnodeId];
				}

				double F = H + tempG;
				priorityQ.push({ neighbor.node, F });


			}

		}
	}
};



bestPath A_Star::A(unordered_map<int, vector<edge>> graph, int sourcePointID, int destinationPointID, double maxSpeed, double R, unordered_map<int, coordinates>coordinate, double timeIntervel, int speedSize)
{
	priority_queue<NodeInfo, vector<NodeInfo>, greater<NodeInfo>> priorityQ;
	priorityQ.push({ sourcePointID, 0 });

	bestPath result;

	unordered_map<int, int> thePath;
	unordered_set<int> visited;
	unordered_map<int, double> gCosts;


	unordered_map<int, double> walkDistances;
	unordered_map<int, double> roadDistances;
	unordered_map<int, double> walkTime;
	unordered_map<int, double> roadTime;


	walkDistances[sourcePointID] = 0;
	roadDistances[sourcePointID] = 0;
	roadTime[sourcePointID] = 0;
	walkTime[sourcePointID] = 0;

	gCosts[sourcePointID] = 0;

	double currentTime = 0;
	double currentSpeed = 0;
	int speedIndex = 0;
	while (!priorityQ.empty())
	{

		int currentnodeId = priorityQ.top().node;
		priorityQ.pop();


		//for the speed changeing 
		currentTime = 60 * (roadTime[currentnodeId]);
		speedIndex = (int)(currentTime / timeIntervel) % speedSize;

		if (currentnodeId == destinationPointID)
		{
			vector<int> path;

			for (int node = thePath[destinationPointID]; node != sourcePointID; node = thePath[node])
				result.nodes.push(node);

			//p.nodes.insert();
			result.walkingDistance = walkDistances[currentnodeId];
			result.roadDistance = roadDistances[currentnodeId];
			result.totalDistance = result.walkingDistance + result.roadDistance;
			double roadInMinutes = (roadTime[currentnodeId]);
			double walkingInMinutes = walkTime[currentnodeId];
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
			double tempG = calcG(currentnodeId, neighbor, gCosts[currentnodeId], speedIndex);

			if (!gCosts.count(neighbor.node) || tempG < gCosts[neighbor.node])
			{

				thePath[neighbor.node] = currentnodeId;
				gCosts[neighbor.node] = tempG;




				if (currentnodeId == sourcePointID) {
					walkDistances[neighbor.node] = neighbor.edgeLength;
					walkTime[neighbor.node] = walkTime[currentnodeId] + calculateWalkingTime(1000 * (neighbor.edgeLength));
				}
				else if (neighbor.node == destinationPointID) {
					walkDistances[neighbor.node] = walkDistances[currentnodeId] + neighbor.edgeLength;
					walkTime[neighbor.node] = walkTime[currentnodeId] + calculateWalkingTime(1000 * (neighbor.edgeLength));
				}
				else {
					walkDistances[neighbor.node] = walkDistances[currentnodeId];
					walkTime[neighbor.node] = walkTime[currentnodeId];
				}

				if (currentnodeId != sourcePointID && neighbor.node != destinationPointID) {
					roadDistances[neighbor.node] = roadDistances[currentnodeId] + neighbor.edgeLength;
					roadTime[neighbor.node] = roadTime[currentnodeId] + calculateRoadTime(neighbor.edgeLength, neighbor.edgeSpeeds[speedIndex]);
				}
				else {
					roadDistances[neighbor.node] = roadDistances[currentnodeId];
					roadTime[neighbor.node] = roadTime[currentnodeId];
				}

				double H = calcH(sourcePointID, destinationPointID, coordinate, maxSpeed, R);
				double F = calcF(H, tempG);
				priorityQ.push({ neighbor.node,F });

			}

		}
	}
};
