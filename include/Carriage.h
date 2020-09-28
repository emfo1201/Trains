//------------------------------------------------------------------------------
// Carriage.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_CARRIAGE_H
#define OO_PROJEKT2019_DEL1_CARRIAGE_H

#include "Vehicle.h"
#include <iostream>

class Carriage : public Vehicle {
private:
public:
    explicit Carriage(int id) : Vehicle(id){ }
    ~Carriage() override = default;
    std::string carType() override = 0;
    std::string printing() override = 0;
};

#endif //OO_PROJEKT2019_DEL1_CARRIAGE_H
