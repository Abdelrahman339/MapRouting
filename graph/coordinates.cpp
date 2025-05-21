#include "coordinates.h"
#include <iostream>
using namespace std;



coordinates::coordinates() {};
coordinates::coordinates(double x_coordinate, double y_coordinate) {};

double coordinates::getX_coordinate() { return this->x_coordinate; };
double coordinates::getY_coordinate() { return this->y_coordinate; };

void coordinates::setX_coordinate(double c) { this->x_coordinate = c; };
void coordinates::setY_coordinate(double c) { this->y_coordinate = c; };


