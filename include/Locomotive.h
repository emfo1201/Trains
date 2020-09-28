//------------------------------------------------------------------------------
// Locomotive.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_LOCOMOTIVE_H
#define OO_PROJEKT2019_DEL1_LOCOMOTIVE_H

#include "Vehicle.h"
#include <iostream>

class Locomotive : public Vehicle {
public:
    explicit Locomotive(int id) : Vehicle(id){}
    ~Locomotive() override = default;
    std::string carType() override = 0;
    std::string printing() override = 0;
};

#endif //OO_PROJEKT2019_DEL1_LOCOMOTIVE_H
