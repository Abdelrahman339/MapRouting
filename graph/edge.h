#pragma once
#include <iostream>
using namespace std;

class edge {

private:



public:
	int node;
	float edgeLength;
	float edgeSpeed;

	int getNode();
	float getlength();
	float getspeed();
	edge();
	edge(int node,float edgeLength,float edgeSpeed);
};