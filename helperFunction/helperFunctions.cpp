#include "helperFunctions.h"
#include <cmath>
using namespace std;

float calculateEuclideanDistance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float calculateTime(float distance, float speed) {
    return distance / speed;
}

//For distances
float kilometerToMeter(float kilo) {
    return kilo*1000;
}

float meterToKilometer(float meter) {
    return meter / 1000;
}

//for time
float hoursToMinutes(float hours) {
    return hours * 60;
}

float minuteToHours(float minutes) {
    return minutes / 60;
}


