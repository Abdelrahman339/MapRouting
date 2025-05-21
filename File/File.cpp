#include "File.h"
#include <chrono>

// ===================================================
// Reads coordinates and constructs the graph 
// Time Complexity: O(|V| + |E|)
// |V|: number of nodes, |E|: number of roads
// ===================================================
void file::readFile(string fileName, unordered_map<int, vector<edge>>& graph, double& maxSpeed, vector<coordinates>& Nodes) {
	string file = fileName;
	ifstream infile(file);
	if (!infile) {
		cout << "Failed to open file.\n";
	}

	// Read node coordinates
	int numberOfnodes;
	infile >> numberOfnodes;
	Nodes.reserve(numberOfnodes);

	int node;
	double x_coordinate, y_coordinate;

	for (int i = 0; i < numberOfnodes; ++i) { // O(|V|)
		infile >> node >> x_coordinate >> y_coordinate;
		coordinates c;
		c.setX_coordinate(x_coordinate);
		c.setY_coordinate(y_coordinate);
		Nodes.push_back(c);
	}

	// Construct the graph
	int numberOfEdges;
	infile >> numberOfEdges;
	int temp;
	edge e;
	int vertex;

	for (int i = 0; i < numberOfEdges; ++i) { // GRAPH CONSTRUCTION => O(|E|)
		infile >> vertex >> e.node >> e.edgeLength >> e.edgeSpeed;
		graph[vertex].push_back(e);
		temp = vertex;
		vertex = e.node;
		e.node = temp;
		graph[vertex].push_back(e); 

		if (e.edgeSpeed > maxSpeed)
			maxSpeed = e.edgeSpeed;
	}
}


// ===================================================
// Reads a list of queries from file
// Time Complexity: O(Q)
// Q = number of queries
// ===================================================
void file::readQuery(string fileName, vector<query>& queries) {
	string file = fileName;
	ifstream infile(file);
	if (!infile) {
		cout << "Failed to open file.\n";
	}

	int numberOfQueries;
	infile >> numberOfQueries;
	query q;

	for (int i = 0; i < numberOfQueries; i++) { // O(Q)
		q.NumOfQueries = numberOfQueries;
		infile >> q.startCoordinate.x_coordinate >> q.startCoordinate.y_coordinate
			>> q.destCoordinate.x_coordinate >> q.destCoordinate.y_coordinate >> q.R;
		q.R = meterToKilometer(q.R);
		queries.push_back(q);
	}
}

// ===================================================
// Writes results of queries to a file
// Time Complexity: O(Q · L)
// Q = number of queries, L = max path length (nodes per bestPath)
// ===================================================
void file::writeFile(string fileName, vector<bestPath> queries,double timeWithIo,double elapsedTimeWithouttIO) {
	auto startIO = std::chrono::high_resolution_clock::now();


	fileName = "Output/" + fileName;
	ofstream file(fileName);

	if (!file.is_open()) {
		cout << "Error opening file!" << endl;
		return;
	}

	for (bestPath path : queries) { // O(Q)
		bool first = true;
		while (!path.nodes.empty()) { // O(L)
			if (!first) file << " ";
			file << path.nodes.front();
			path.nodes.pop_front();
			first = false;
		}
		file << "\n";

		// Write time
		file << fixed << setprecision(2) << path.time << " mins\n";

		// Write distances
		file << path.totalDistance << " km\n";
		file << path.walkingDistance << " km\n";
		file << path.roadDistance << " km\n";

		file << "\n";
	}
	auto endIO = std::chrono::high_resolution_clock::now();
	double elapsedTimeWithIOAfterWrite = std::chrono::duration<double, milli>(startIO - endIO).count();
	file << elapsedTimeWithouttIO << " ms";
	file << "\n";
	file << "\n";
	file << timeWithIo+elapsedTimeWithIOAfterWrite<<" ms";
	file<<"\n";

	

	file.close();
}
