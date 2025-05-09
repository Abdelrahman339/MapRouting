#pragma once
#include <iostream>
#include "unordered_map"
#include "vector"
using namespace std;

class coordinates {

public:
	float x_coordinate, y_coordinate;	
	coordinates();
	coordinates(float x_coordinate, float y_coordinate);
	float getX_coordinate();
	float getY_coordinate();
	void setX_coordinate(float c);
	void setY_coordinate(float c);

	void printCoordinates(unordered_map<int, coordinates> coor);
};


