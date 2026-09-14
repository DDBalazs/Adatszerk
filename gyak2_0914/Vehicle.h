//
// Created by csoke on 2026. 09. 14..
//

#ifndef GYAK2_0914_VEHICLE_H
#define GYAK2_0914_VEHICLE_H
#include <string>
using namespace std;

class Vehicle {
private:
    string type;
    double kmh;
    int capacity;
public:
    Vehicle(string type, double kmh, int capacity);
    string getType();
    double getKmh();
    int getCapacity();
    double virtual moveOn();
};

#endif //GYAK2_0914_VEHICLE_H
