#pragma once
#include <iostream>
#include "unordered_map"
#include "vector"
using namespace std;

class coordinates {

public:
	double x_coordinate, y_coordinate;	
	coordinates();
	coordinates(double x_coordinate, double y_coordinate);
	double getX_coordinate();
	double getY_coordinate();
	void setX_coordinate(double c);
	void setY_coordinate(double c);

	void printCoordinates(unordered_map<int, coordinates> coor);
};


