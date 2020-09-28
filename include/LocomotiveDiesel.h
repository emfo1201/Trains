//------------------------------------------------------------------------------
// LocomotiveDiesel.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_LOCOMOTIVEDIESEL_H
#define OO_PROJEKT2019_DEL1_LOCOMOTIVEDIESEL_H

#include "Locomotive.h"
#include <iostream>
#include <string>

class LocomotiveDiesel : public Locomotive {
private:
    int maxSpeed, fuelConsumption;
    std::string type = "Diesel locomotive";
public:
    explicit LocomotiveDiesel(int id, int iMaxSpeed, int iFuelConsumption) : Locomotive(id), maxSpeed(iMaxSpeed), fuelConsumption(iFuelConsumption){}
    ~LocomotiveDiesel() override = default;
    std::string carType() override { return type; };
    std::string printing() override { return + "max speed: " + std::to_string(maxSpeed) + " km/h, fuel consumption: " + std::to_string(fuelConsumption) + " l/h"; }
};

#endif //OO_PROJEKT2019_DEL1_LOCOMOTIVEDIESEL_H
