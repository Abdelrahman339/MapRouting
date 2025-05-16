#include "A_Star.h"
#include <functional>





double A_Star::calcF(double h, double g) {
	return h + g;
};

double A_Star::calcH(int startPointID, int destinationPointId, const vector <coordinates> &coordinate, double maxSpeed, double R) {
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

bestPath A_Star::A(const unordered_map<int, vector<edge>> &graph, int sourcePointID, int destinationPointID, double maxSpeed, double R, const vector<coordinates>&coordinate)
{
	priority_queue<NodeInfo, vector<NodeInfo>, greater<NodeInfo>> priorityQ;
	priorityQ.push({ sourcePointID, 0, 0, 0, 0, 0 });
	bestPath result;

	unordered_map<int, int> thePath;
	unordered_set<int> visited;
	unordered_map<int, double> gCosts;

	gCosts[sourcePointID] = 0;

	double H = calcH(sourcePointID, destinationPointID, coordinate, maxSpeed, R);

	while (!priorityQ.empty())
	{

		NodeInfo current = priorityQ.top();
		priorityQ.pop();
		if (current.node == destinationPointID)
		{
			vector<int> path;

			for (int node = thePath[destinationPointID]; node != sourcePointID; node = thePath[node])
				result.nodes.push_front(node);

			//p.nodes.insert();
			result.walkingDistance = current.walkDist;
			result.roadDistance = current.roadDist;
			result.totalDistance = roundUp(current.walkDist + current.roadDist);
			result.time = roundUp(current.walkTime + current.roadTime * 60);
			return result;
		}
		auto temp = visited.find(current.node);
		if (temp != visited.end())
			continue;
		visited.insert(current.node);



		for (edge neighbor : graph.at(current.node))
		{
			//calc the g , h and f for each neighbor 
			double tempG = calcG(current.node, neighbor, gCosts[current.node]);
			auto it = gCosts.find(neighbor.node);
			if (it == gCosts.end() || tempG < it->second)
			{

				thePath[neighbor.node] = current.node;
				gCosts[neighbor.node] = tempG;


				double newWalkDist = current.walkDist;
				double newRoadDist = current.roadDist;
				double newWalkTime = current.walkTime;
				double newRoadTime = current.roadTime;

				if (current.node == sourcePointID || neighbor.node == destinationPointID) {
					newWalkDist += neighbor.edgeLength;
					newWalkTime += (1000 * neighbor.edgeLength) / ((walkingSpeed * 1000) / 60);  // minutes
				}
				else {
					newRoadDist += neighbor.edgeLength;
					newRoadTime += neighbor.edgeLength / neighbor.edgeSpeed; // hours
				}

				
				double F = H + tempG;
				priorityQ.push({ neighbor.node, F,newWalkDist,newRoadDist,newWalkTime,newRoadTime });


			}

		}
	}
};



//bestPath A_Star::A(unordered_map<int, vector<edge>> graph, int sourcePointID, int destinationPointID, double maxSpeed, double R, unordered_map<int, coordinates>coordinate, double timeIntervel, int speedSize)
//{
//	//priority_queue<NodeInfo, vector<NodeInfo>, greater<NodeInfo>> priorityQ;
//	//priorityQ.push({ sourcePointID, 0, 0, 0, 0, 0 });
//
//
//	//bestPath result;
//
//	//unordered_map<int, int> thePath;
//	//unordered_set<int> visited;
//	//unordered_map<int, double> gCosts;
//
//
//	//unordered_map<int, double> walkDistances;
//	//unordered_map<int, double> roadDistances;
//	//unordered_map<int, double> walkTime;
//	//unordered_map<int, double> roadTime;
//
//
//	//walkDistances[sourcePointID] = 0;
//	//roadDistances[sourcePointID] = 0;
//	//roadTime[sourcePointID] = 0;
//	//walkTime[sourcePointID] = 0;
//
//	//gCosts[sourcePointID] = 0;
//
//	//double currentTime = 0;
//	//double currentSpeed = 0;
//	//int speedIndex = 0;
//	//while (!priorityQ.empty())
//	//{
//
//	//	NodeInfo current = priorityQ.top();
//	//	priorityQ.pop();
//
//
//	//	//for the speed changeing 
//	//	currentTime = 60 * (roadTime[current.node]);
//	//	speedIndex = (int)(currentTime / timeIntervel) % speedSize;
//
//	//	if (current.node == destinationPointID)
//	//	{
//	//		vector<int> path;
//
//	//		for (int node = thePath[destinationPointID]; node != sourcePointID; node = thePath[node])
//	//			result.nodes.push(node);
//
//	//		//p.nodes.insert();
//	//		result.walkingDistance = walkDistances[current.node];
//	//		result.roadDistance = roadDistances[current.node];
//	//		result.totalDistance = result.walkingDistance + result.roadDistance;
//	//		double roadInMinutes = (roadTime[current.node]);
//	//		double walkingInMinutes = walkTime[current.node];
//	//		result.time = walkingInMinutes + roadInMinutes;
//	//		return result;
//	//	}
//
//	//	if (visited.count(current.node))
//	//		continue;
//	//	visited.insert(current.node);
//
//	//	vector<edge> neighbors = graph[current.node];
//
//
//
//	//	for (edge neighbor : neighbors)
//	//	{
//	//		//calc the g , h and f for each neighbor 
//	//		double tempG = calcG(current.node, neighbor, gCosts[current.node], speedIndex);
//
//	//		if (!gCosts.count(neighbor.node) || tempG < gCosts[neighbor.node])
//	//		{
//
//	//			thePath[neighbor.node] = current.node;
//	//			gCosts[neighbor.node] = tempG;
//
//
//
//
//	//			if (current.node == sourcePointID) {
//	//				walkDistances[neighbor.node] = neighbor.edgeLength;
//	//				walkTime[neighbor.node] = walkTime[current.node] + calculateWalkingTime(1000 * (neighbor.edgeLength));
//	//			}
//	//			else if (neighbor.node == destinationPointID) {
//	//				walkDistances[neighbor.node] = walkDistances[current.node] + neighbor.edgeLength;
//	//				walkTime[neighbor.node] = walkTime[current.node] + calculateWalkingTime(1000 * (neighbor.edgeLength));
//	//			}
//	//			else {
//	//				walkDistances[neighbor.node] = walkDistances[current.node];
//	//				walkTime[neighbor.node] = walkTime[current.node];
//	//			}
//
//	//			if (current.node != sourcePointID && neighbor.node != destinationPointID) {
//	//				roadDistances[neighbor.node] = roadDistances[current.node] + neighbor.edgeLength;
//	//				roadTime[neighbor.node] = roadTime[current.node] + calculateRoadTime(neighbor.edgeLength, neighbor.edgeSpeeds[speedIndex]);
//	//			}
//	//			else {
//	//				roadDistances[neighbor.node] = roadDistances[current.node];
//	//				roadTime[neighbor.node] = roadTime[current.node];
//	//			}
//
//	//			double H = calcH(sourcePointID, destinationPointID, coordinate, maxSpeed, R);
//	//			double F = calcF(H, tempG);
//	//			priorityQ.push({ neighbor.node,F });
//
//	//		}
//
//	//	}
//	//}
//
//};
