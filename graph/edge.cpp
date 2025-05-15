#include "edge.h"

edge::edge() {};
edge::edge(int node, double edgeLength, double edgeSpeed) {};


int   edge::getNode() { return this->node; };
double edge::getlength() { return this->edgeLength; };

//double edge::getspeed() { return this->edgeSpeed; };

void edge::printEdges(unordered_map<int, vector<edge>> edges)
{
	//for (const auto& [from, edgeList] : edges) {
	//	cout << "Node " << from << " has edges:\n";
	//	for (const auto& edge : edgeList) {
	//		cout << "  -> " << edge.node
	//			<< " (length: " << edge.edgeLength
	//			<< ", speed: " << edge.edgeSpeed << ")\n";
	//	}
	//}
};
