//
// Created by Arpad on 2026. 09. 15..
//

#ifndef ADATSZERKEZETEK_CAR_H
#define ADATSZERKEZETEK_CAR_H
#include "Vehicle.hpp"
using namespace std;
class Car : public Vehicle{
    double consumption;
    double petrol;
    public:
    static const int petrolCost = 600;
    Car(string type, double consumption, int capacity, double kmh = 0) : Vehicle(type,kmh,capacity), consumption(consumption) {
        petrol = 100;
    };
    static int getCost(int liter){return petrolCost*liter;};
    virtual void refuel(double liter) {petrol += liter;};
    virtual double cost(double km) {return getCost(km/100*consumption);};
    double getConsumption(){return consumption;}
    double getPetrol(){return petrol;}

    void moveOn(double amount) override {
        if (petrol/consumption*100 < amount) {
            cout <<"Nincs elég benzin"<< endl;
            return;
        }
        cout << "Kocsival megyünk: "<< amount << endl;
        kmh += amount;
        petrol -= amount/100*consumption;
    }
    virtual ~Car() = default;
};

#endif //ADATSZERKEZETEK_CAR_H