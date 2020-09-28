//------------------------------------------------------------------------------
// CarriagePassengerCarSleep.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_CARRIAGESLEEP_H
#define OO_PROJEKT2019_DEL1_CARRIAGESLEEP_H

#include "CarriagePassengerCar.h"
#include <iostream>
#include <string>

class CarriagePassengerCarSleep : public CarriagePassengerCar{
private:
    int beds;
    std::string type = "Passenger car, sleep";
public:
    explicit CarriagePassengerCarSleep(int id, int iBeds) : CarriagePassengerCar(id), beds(iBeds){}
    ~CarriagePassengerCarSleep() override = default;
    std::string carType() override { return type; };
    std::string printing() override { return ", " + std::to_string(beds) + " beds"; }
};

#endif //OO_PROJEKT2019_DEL1_CARRIAGESLEEP_H
