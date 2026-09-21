//
// Created by Arpad on 2026. 09. 21..
//

#ifndef ADATSZERKEZETEK_BUS_H
#define ADATSZERKEZETEK_BUS_H

#include "Taxi.h"
using namespace std;
class Bus : public Taxi {
    public:
    static const int ticketCost = 500;
    Bus(string type,double cconsumption,int capacity, double kmCost)
    : Taxi(type,cconsumption,capacity,kmCost) {};
    double carriage(double km){return km * kmCost;};
    double memberCost(double km,double member){return carriage(km,member) / member;};
    double carriage(double km,double member){return  km * kmCost * member;};
    double profit(double km, double member) {
        double income = member * ticketCost;
        double expense = cost(km);
        double p = income - expense;
        return p;
    };
    virtual ~Bus() = default;



};

#endif //ADATSZERKEZETEK_BUS_H