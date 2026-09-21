//
// Created by Arpad on 2026. 09. 15..
//

#ifndef ADATSZERKEZETEK_VEHICLE_HPP
#define ADATSZERKEZETEK_VEHICLE_HPP
using namespace std;
class Vehicle {
protected:
    string type;
    double kmh;
    int capacity;
    public:
    Vehicle(string type, double kmh, int capacity): type(type), kmh(kmh), capacity(capacity) {};
    string getType() const{return type;}
    double getKmh() const{return kmh;}
    int getCapacity() const{return capacity;}
    virtual void moveOn(double km) = 0;
    virtual ~Vehicle() = default;
};
#endif //ADATSZERKEZETEK_VEHICLE_HPP