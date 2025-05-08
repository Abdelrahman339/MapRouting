#include "edge.h"

edge::edge() {};
edge::edge(int node, float edgeLength, float edgeSpeed) {};
 
 
int   edge::getNode() {
	return this->node;
};
float edge::getlength() { return this->edgeLength; };
float edge::getspeed() { return this->edgeSpeed; };