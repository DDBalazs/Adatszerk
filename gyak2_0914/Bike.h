//
// Created by Arpad on 2026. 09. 15..
//

#ifndef ADATSZERKEZETEK_BIKE_H
#define ADATSZERKEZETEK_BIKE_H
#include "Vehicle.hpp"
using namespace std;
class Bike : public Vehicle {
public:
    Bike(string type) : Vehicle(type, 0, 1) {}
    virtual ~Bike() = default;

    virtual void moveOn(double km) override {
        kmh += km;
    }
};

#endif //ADATSZERKEZETEK_BIKE_H