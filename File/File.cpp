#include "File.h"



file::file() {

	cout << "file";
}
unordered_map<int ,coordinates> file::readFile(string fileName,string typeOftest, unordered_map<int, vector<edge>>&graph) {
	string dir = "Data/testCases/";
	dir = dir + typeOftest + "/";
	string file = dir + fileName+".txt";

	int numberOfnodes;
	ifstream infile(file);
	if (!infile) {
		cout<< "Failed to open file.\n";
	}
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


	int numberOfEdges;
	infile >> numberOfEdges;
	vector <edge> edges;

	for (int i = 0; i < numberOfEdges; ++i) {
		edge e;
		int node1;
		infile >> node1 >> e.node>> e.edgeLength>> e.edgeSpeed;
		graph[node1].push_back(e);
	}



	cout << "file name:" << file<<endl;



	for (auto& [node, coords] : Nodes) {
		cout << "ID: " << node << " => (" << coords.getX_coordinate() << ", " << coords.getY_coordinate()<< ")\n";
	}

	for (const auto& [from, edgeList] : graph) {
		cout << "Node " << from << " has edges:\n";
		for (const auto& edge : edgeList) {
			cout << "  -> " << edge.node
				<< " (length: " << edge.edgeLength
				<< ", speed: " << edge.edgeSpeed << ")\n";
		}
	}

	return Nodes;
}