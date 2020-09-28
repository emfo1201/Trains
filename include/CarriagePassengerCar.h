//------------------------------------------------------------------------------
// CarriagePassengerCar.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_CARRIAGEPEOPLE_H
#define OO_PROJEKT2019_DEL1_CARRIAGEPEOPLE_H

#include "../include/Carriage.h"
#include <iostream>

class CarriagePassengerCar : public Carriage {
private:
public:
    explicit CarriagePassengerCar(int id) : Carriage(id) { }
    ~CarriagePassengerCar() override = default;
    std::string carType() override = 0;
    std::string printing() override = 0;
};

#endif //OO_PROJEKT2019_DEL1_CARRIAGEPEOPLE_H
