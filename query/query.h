#pragma once
#include <iostream>
#include "../graph/coordinates.h"
using namespace std;

class query {

public:
	static int NumOfQueries;
	coordinates startCoordinate;
	coordinates destCoordinate;
	float R;


};