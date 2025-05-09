#include "File.h"



unordered_map<int ,coordinates> file::readFile(string fileName,string typeOftest, unordered_map<int, vector<edge>>&graph,float &maxSpeed) {
	
	//file info
	string dir = "Data/testCases/";
	dir = dir + typeOftest + "/";
	string file = dir + fileName+".txt";
	ifstream infile(file);
	if (!infile) {
		cout<< "Failed to open file.\n";
	}


	//coordinates of each node 
	int numberOfnodes;
	unordered_map <int, coordinates> Nodes;
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
	float max = -1;
	for (int i = 0; i < numberOfEdges; ++i) {
		edge e;
		int vertex;
		infile >> vertex >> e.node>> e.edgeLength>> e.edgeSpeed;
		graph[vertex].push_back(e);

		if (e.edgeSpeed > max)
			max = e.edgeSpeed;
	}
	return Nodes;
}

vector<query> file::readQery(string fileName) 
{
	//file info
	string dir = "Data/testCases/";
	string file = dir + fileName + ".txt";
	ifstream infile(file);
	if (!infile) {
		cout << "Failed to open file.\n";
	}

	//query constract

	int queryNumber;
	vector<query> queries;
	infile >> queryNumber;
	query q;

	for (int i = 0; i < queryNumber; i++)
	{	
		infile >> q.startCoordinate.x_coordinate>>q.startCoordinate.y_coordinate>>q.destCoordinate.x_coordinate>>q.destCoordinate.y_coordinate>>q.R;
		queries.push_back(q);
	}

	return queries;
};
