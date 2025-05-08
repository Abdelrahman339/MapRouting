#include "coordinates.h"
#include <iostream>
using namespace std;



coordinates::coordinates() {};
coordinates::coordinates(float x_coordinate, float y_coordinate) {};

float coordinates::getX_coordinate() { return this->x_coordinate; };
float coordinates::getY_coordinate() { return this->y_coordinate; };

void coordinates::setX_coordinate(float c) { this->x_coordinate = c; };
void coordinates::setY_coordinate(float c) { this->y_coordinate = c; };
