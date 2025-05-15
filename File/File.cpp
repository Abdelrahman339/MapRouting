#include "File.h"



void file::readFile(string fileName ,unordered_map<int, vector<edge>>& graph, double& maxSpeed, vector<coordinates> &Nodes){

	//file info

	string file = fileName;
	ifstream infile(file);
	if (!infile) {
		cout << "Failed to open file.\n";
	}


	//coordinates of each node 
	int numberOfnodes;
	infile >> numberOfnodes;
	Nodes.reserve(numberOfnodes);

	int node;
	double x_coordinate, y_coordinate;


	for (int i = 0; i < numberOfnodes; ++i)
	{
		infile >> node >> x_coordinate >> y_coordinate;
		coordinates c;
		c.setX_coordinate(x_coordinate);
		c.setY_coordinate(y_coordinate);
		Nodes.push_back(c);
	
	}


	//graph construction 
	int numberOfEdges;
	infile >> numberOfEdges;
	int temp;
	edge e;
	int vertex;
	for (int i = 0; i < numberOfEdges; ++i) {
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
void file::readFile(string fileName, unordered_map<int, vector<edge>>& graph, double& maxSpeed, double& Speed_Interval,int&speedSize, unordered_map <int, coordinates>& Nodes) {

	//file info
	string file = fileName;
	ifstream infile(file);
	if (!infile) {
		cout << "Failed to open file.\n";
	}

	//coordinates of each node 
	int numberOfnodes;
	infile >> numberOfnodes;

	int node;
	float x_coordinate, y_coordinate;



	for (int i = 0; i < numberOfnodes; ++i)
	{
		infile >> node >> x_coordinate >> y_coordinate;
		coordinates c;
		c.setX_coordinate(x_coordinate);
		c.setY_coordinate(y_coordinate);
		Nodes[node] = c;
	}


	//graph construction 
	int numberOfEdges;
	infile >> numberOfEdges;
	int temp;
	edge e;
	int vertex;
	for (int i = 0; i < numberOfEdges; ++i) {
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

void file::readQuery(string fileName, vector<query> &queries)
{
	string file = fileName;
	ifstream infile(file);
	if (!infile) {
		cout << "Failed to open file.\n";
	}

	//query constract

	int numberOfQueries;
	infile >> numberOfQueries;
	query q;

	for (int i = 0; i < numberOfQueries; i++)
	{
		q.NumOfQueries = numberOfQueries;
		infile >> q.startCoordinate.x_coordinate >> q.startCoordinate.y_coordinate >> q.destCoordinate.x_coordinate >> q.destCoordinate.y_coordinate >> q.R;
		q.R = meterToKilometer(q.R);
		queries.push_back(q);
	}

};

void file::writeFile(string fileName, vector<bestPath> queries)
{
	fileName = "Output/" + fileName;
	ofstream file(fileName);

	if (!file.is_open()) {
	cout<<"Error opening file!" <<endl;
		return;
	}

	for (bestPath path : queries) {

		bool first = true;
		while (!path.nodes.empty()) {
			if (!first) file << " ";
			file << path.nodes.top();
			path.nodes.pop();
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

	file.close();
}
