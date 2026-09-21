//
// Created by Arpad on 2026. 09. 18..
//

#ifndef ADATSZERKEZETEK_TAXI_H
#define ADATSZERKEZETEK_TAXI_H
#include "Vehicle.hpp"
#include "Car.h"
using namespace std;
class Taxi : public Car {
protected:
    double pocket;
    double kmCost;
    public:
    Taxi(string type, double consumption, int capacity, double kmCost):
    pocket(0)   ,Car(type,consumption,capacity),kmCost(kmCost){};
    virtual double cost(double km)override {
        return km * kmCost;
    };
    virtual void refuel(double liter)override {
        double price = liter * petrolCost;
        pocket -= price;
        Car::refuel(liter);
    };
    double carriage(double km){return km*kmCost;};
    double memberCost(double km, double memeber){ return carriage(km)/memeber;};
    double getKmCost(){return kmCost;};
    double getPocket(){return pocket;};
    virtual ~Taxi() = default;


};

#endif //ADATSZERKEZETEK_TAXI_H