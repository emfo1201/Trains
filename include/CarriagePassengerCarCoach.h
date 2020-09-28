//------------------------------------------------------------------------------
// CarriagePassengerCarCoach.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_CARRIAGECOACH_H
#define OO_PROJEKT2019_DEL1_CARRIAGECOACH_H

#include "CarriagePassengerCar.h"
#include <iostream>
#include <string>

class CarriagePassengerCarCoach : public CarriagePassengerCar{
private:
    int seats;
    bool internet;
    std::string type = "Passenger car, coach";
public:
    explicit CarriagePassengerCarCoach(int id, int iSeats, bool iInternet) : CarriagePassengerCar(id), seats(iSeats), internet(iInternet){}
    ~CarriagePassengerCarCoach() override = default;
    std::string carType() override { return type; }
    std::string printing() override {
            std::string availableInternet;
        (internet) ?
        availableInternet = std::to_string(seats) + " seats, internet onboard" :
        availableInternet = std::to_string(seats) + " seats, no internet onboard";
        return availableInternet;
    }

};

#endif //OO_PROJEKT2019_DEL1_CARRIAGECOACH_H
