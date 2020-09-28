//------------------------------------------------------------------------------
// LocomotiveElectric.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_LOCOMOTIVEELECTRIC_H
#define OO_PROJEKT2019_DEL1_LOCOMOTIVEELECTRIC_H

#include "Locomotive.h"
#include <iostream>
#include <string>

class LocomotiveElectric : public Locomotive {
private:
    int maxSpeed, power;
    std::string type = "Electric locomotive";
public:
    explicit LocomotiveElectric(int id, int iMaxSpeed, int iPower) : Locomotive(id), maxSpeed(iMaxSpeed), power(iPower){}
    ~LocomotiveElectric() override = default;
    std::string carType() override { return type; };
    std::string printing() override { return " max speed: " + std::to_string(maxSpeed) + " km/h, power: " + std::to_string(power) + " kw"; }
};

#endif //OO_PROJEKT2019_DEL1_LOCOMOTIVEELECTRIC_H
