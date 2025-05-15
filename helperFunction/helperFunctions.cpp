#include "helperFunctions.h"


using namespace std;



float calculateEuclideanDistance(int startPointId, int goalPointId, unordered_map<int, coordinates> Nodes) {
	float startX = Nodes[startPointId].x_coordinate;
	float startY = Nodes[startPointId].y_coordinate;
	float goalX = Nodes[goalPointId].x_coordinate;
	float goalY = Nodes[goalPointId].y_coordinate;

	float X = pow(goalX - startX, 2);
	float Y = pow(goalY - startY, 2);

	return sqrt(X + Y);
}

float calculateEuclideanDistance(int startPointId, float destx, float destY, unordered_map<int, coordinates> Nodes)
{
	float startX = Nodes[startPointId].x_coordinate;
	float goalY = Nodes[startPointId].y_coordinate;


	float X = pow(destx - startX, 2);
	float Y = pow(destY - goalY, 2);

	return sqrt(X + Y);
}









unordered_map<int, float> getNodesWithinRadiusGrid(float targetX,float targetY,float radius,unordered_map<int, coordinates>& Nodes,unordered_map<string, vector<int>>& spatialGrid,float cellSize) {
	unordered_map<int, float> result;
	float rSquared = radius * radius;

	
	int cellX = static_cast<int>(floor(targetX / cellSize));
	int cellY = static_cast<int>(floor(targetY / cellSize));


	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			string neighborKey = to_string(cellX + dx) + "_" + to_string(cellY + dy);
			if (spatialGrid.count(neighborKey)) {
				for (int nodeId : spatialGrid.at(neighborKey)) {
					const auto& coord = Nodes.at(nodeId);
					float dx = coord.x_coordinate - targetX;
					float dy = coord.y_coordinate - targetY;
					float distSq = dx * dx + dy * dy;

					if (distSq <= rSquared) {
						result[nodeId] = sqrt(distSq);
					}
				}
			}
		}
	}

	return result;
}

unordered_map<int, float> getNodesWithinRadius(float targetX, float targetY, float radius, unordered_map<int, coordinates> Nodes) {

	unordered_map<int, float>result;
	//iterate over all nodes => N-1
	//for now O(Nodes) , may be changed later

	for (const auto& pair : Nodes) {
		int nodeId = pair.first;
		coordinates coord = pair.second;
		float nodeX = coord.getX_coordinate();
		float nodeY = coord.getY_coordinate();
		float distance = calculateEuclideanDistance(nodeId, targetX, targetY, Nodes);
		if (distance <= radius)
			result[nodeId] = distance;


	}
	return result;
}

float calculateRoadTime(float distance, float speed) {
	return (distance / speed);
}

float calculateWalkingTime(float distance) {
	float walkSpeedInMeterPerMin = ((walkingSpeed * 1000) / 60);
	return distance / walkSpeedInMeterPerMin;

}

//For distances
float kilometerToMeter(float kilo) {
	return kilo * 1000.0f;
}

float meterToKilometer(float meter) {
	return meter / 1000.0f;
}

//for time
float hoursToMinutes(float hours) {
	return hours * 60.0f;
}

float minuteToHours(float minutes) {
	return minutes / 60.0f;
}

float truncateTwoDecimals(float value) {
	return static_cast<int>(value * 100) / 100.0;
}

int addNode(unordered_map<int, vector<edge>>& graph, unordered_map<int, float>points) {

	int nodeId = graph.size();
	for (auto& [ponitID, distance] : points)
	{
		edge edge;
		edge.node = ponitID;
		edge.edgeSpeed = 5;
		for (int i = 0; i <graph[0][0].edgeSpeeds.size(); i++)
		{
		edge.edgeSpeeds.push_back(5);
		}
		edge.edgeLength = distance;
		edge.cost = 5 / distance;
		graph[nodeId].push_back(edge);
		edge.node = nodeId;
		graph[ponitID].push_back(edge);
	}
	return nodeId;
};

void addNode(unordered_map<int, coordinates>& coordinate, coordinates coor)
{
	int coorId = coordinate.size();
	coordinate[coorId] = coor;
};
