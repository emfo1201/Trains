//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-06-02
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_STATION_H
#define OO_PROJEKT2019_STATION_H

#include <iostream>

class Station{
private:
    std::string st1, st2;
    double dist;
public:
    Station(std::string station1, std::string station2, double distance) : st1(std::move(station1)), st2(std::move(station2)), dist(distance) {}
    // Get functions
    std::string getStation1() { return st1; }
    std::string getStation2() { return st2; }
    double getDistance() { return dist; }
};
#endif //OO_PROJEKT2019_STATION_H
