//------------------------------------------------------------------------------
// Vehicle.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_VEHICLE_H
#define OO_PROJEKT2019_DEL1_VEHICLE_H

#include <iostream>
#include <string>

class Vehicle {
private:
    int id;
protected:
    int const maxSpeed;
public:
    explicit Vehicle(int iId) : id(iId), maxSpeed(0){}
    virtual ~Vehicle() = default;
    virtual std::string carType() = 0;
    virtual std::string printing() = 0;
    int getId() const { return id; }
};
#endif //OO_PROJEKT2019_DEL1_VEHICLE_H
