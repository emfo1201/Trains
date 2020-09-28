//------------------------------------------------------------------------------
// CarriageGoodsWagonCovered.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_CARRIAGECLOSEDFREIGHT_H
#define OO_PROJEKT2019_DEL1_CARRIAGECLOSEDFREIGHT_H

#include "CarriageGoodsWagon.h"
#include <iostream>
#include <string>

class CarriageGoodsWagonCovered : public CarriageGoodsWagon {
private:
    std::string type = "Covered goods wagon";
    int volume;

public:
    explicit CarriageGoodsWagonCovered(int id, int iVolume) : CarriageGoodsWagon(id), volume(iVolume) { }
    ~CarriageGoodsWagonCovered() override = default;
    std::string carType() override { return type; };
    std::string printing() override { return "Cargo volume: " + std::to_string(volume) + " m^3"; }
};

#endif //OO_PROJEKT2019_DEL1_CARRIAGECLOSEDFREIGHT_H
