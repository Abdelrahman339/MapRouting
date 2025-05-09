#include "edge.h"

edge::edge() {};
edge::edge(int node, float edgeLength, float edgeSpeed) {};


int   edge::getNode() { return this->node; };
float edge::getlength() { return this->edgeLength; };
float edge::getspeed() { return this->edgeSpeed; };

void edge::printEdges(unordered_map<int, vector<edge>> edges)
{
	for (const auto& [from, edgeList] : edges) {
		cout << "Node " << from << " has edges:\n";
		for (const auto& edge : edgeList) {
			cout << "  -> " << edge.node
				<< " (length: " << edge.edgeLength
				<< ", speed: " << edge.edgeSpeed << ")\n";
		}
	}
};
