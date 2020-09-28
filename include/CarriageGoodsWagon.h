//------------------------------------------------------------------------------
// CarriageGoodsWagon.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_CARRIAGEFREIGHT_H
#define OO_PROJEKT2019_DEL1_CARRIAGEFREIGHT_H

#include "Carriage.h"
#include <iostream>

class CarriageGoodsWagon : public Carriage {
protected:
    explicit CarriageGoodsWagon(int id) : Carriage(id) {}
    ~CarriageGoodsWagon() override = default;
    std::string carType() override = 0;
    std::string printing() override = 0;
};

#endif //OO_PROJEKT2019_DEL1_CARRIAGEFREIGHT_H
