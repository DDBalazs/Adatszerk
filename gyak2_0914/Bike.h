//
// Created by csoke on 2026. 09. 14..
//

#ifndef GYAK2_0914_BIKE_H
#define GYAK2_0914_BIKE_H
#include "Vehicle.h"
#include <string>
using namespace std;

class Bike : public  Vehicle {
private:

public:
    Bike(string type, double kmh, int capacity);
    Bike(moveOn(kmh));
};

#endif //GYAK2_0914_BIKE_H
