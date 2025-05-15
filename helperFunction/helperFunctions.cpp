#include "helperFunctions.h"


using namespace std;



double calculateEuclideanDistance(int startPointId, int goalPointId, unordered_map<int, coordinates> Nodes) {
	double startX = Nodes[startPointId].x_coordinate;
	double startY = Nodes[startPointId].y_coordinate;
	double goalX = Nodes[goalPointId].x_coordinate;
	double goalY = Nodes[goalPointId].y_coordinate;

	double X = pow(goalX - startX, 2);
	double Y = pow(goalY - startY, 2);

	return sqrt(X + Y);
}

double calculateEuclideanDistance(int startPointId, double destx, double destY, unordered_map<int, coordinates> Nodes)
{
	double startX = Nodes[startPointId].x_coordinate;
	double goalY = Nodes[startPointId].y_coordinate;


	double X = pow(destx - startX, 2);
	double Y = pow(destY - goalY, 2);

	return sqrt(X + Y);
}









unordered_map<int, double> getNodesWithinRadiusGrid(double targetX,double targetY,double radius,unordered_map<int, coordinates>& Nodes,unordered_map<string, vector<int>>& spatialGrid,double cellSize) {
	unordered_map<int, double> result;
	double rSquared = radius * radius;

	
	int cellX = static_cast<int>(floor(targetX / cellSize));
	int cellY = static_cast<int>(floor(targetY / cellSize));


	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			string neighborKey = to_string(cellX + dx) + "_" + to_string(cellY + dy);
			if (spatialGrid.count(neighborKey)) {
				for (int nodeId : spatialGrid.at(neighborKey)) {
					const auto& coord = Nodes.at(nodeId);
					double dx = coord.x_coordinate - targetX;
					double dy = coord.y_coordinate - targetY;
					double distSq = dx * dx + dy * dy;

					if (distSq <= rSquared) {
						result[nodeId] = sqrt(distSq);
					}
				}
			}
		}
	}

	return result;
}

unordered_map<int, double> getNodesWithinRadius(double targetX, double targetY, double radius, unordered_map<int, coordinates> Nodes) {

	unordered_map<int, double>result;
	//iterate over all nodes => N-1
	//for now O(Nodes) , may be changed later

	for (const auto& pair : Nodes) {
		int nodeId = pair.first;
		coordinates coord = pair.second;
		double nodeX = coord.getX_coordinate();
		double nodeY = coord.getY_coordinate();
		double distance = calculateEuclideanDistance(nodeId, targetX, targetY, Nodes);
		if (distance <= radius)
			result[nodeId] = distance;


	}
	return result;
}

double calculateRoadTime(double distance, double speed) {
	return (distance / speed);
}

double calculateWalkingTime(double distance) {
	double walkSpeedInMeterPerMin = ((walkingSpeed * 1000) / 60);
	return distance / walkSpeedInMeterPerMin;

}

//For distances
double kilometerToMeter(double kilo) {
	return kilo * 1000.0f;
}

double meterToKilometer(double meter) {
	return meter / 1000.0f;
}

//for time
double hoursToMinutes(double hours) {
	return hours * 60.0f;
}

double minuteToHours(double minutes) {
	return minutes / 60.0f;
}

double truncateTwoDecimals(double value) {
	return static_cast<int>(value * 100) / 100.0;
}

int addNode(unordered_map<int, vector<edge>>& graph, unordered_map<int, double>points) {

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
double roundUp(double number) 
{
	return round(number * 100.0f) / 100.0f;
}