//------------------------------------------------------------------------------
// CarriageGoodsWagonOpen.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_CARRIAGEOPENFREIGHT_H
#define OO_PROJEKT2019_DEL1_CARRIAGEOPENFREIGHT_H

#include "CarriageGoodsWagon.h"
#include <iostream>
#include <string>

class CarriageGoodsWagonOpen : public CarriageGoodsWagon {
private:
    std::string type = "Open goods wagon";
    int capacity, cargoArea;
public:
    explicit CarriageGoodsWagonOpen(int id, int iCapacity, int iCargoArea) : CarriageGoodsWagon(id), capacity(iCapacity), cargoArea(iCargoArea) { }
    ~CarriageGoodsWagonOpen() override = default;
    std::string carType() override { return type; };
    std::string printing() override { return "cargo capacity: " + std::to_string(capacity) + " ton, cargo area " + std::to_string(cargoArea) + " m^2"; }
};

#endif //OO_PROJEKT2019_DEL1_CARRIAGEOPENFREIGHT_H
