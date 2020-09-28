//------------------------------------------------------------------------------
// Trains.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-26
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_DEL1_TRAINS_H
#define OO_PROJEKT2019_DEL1_TRAINS_H
#include <iostream>
#include "Constants.h"


class Trains{
private:
    int id;
    std::string fromStation, toStation, wagons;
    int depTime, arrTime, delayedDepTime, delayedArrTime, delayedTime;
    double maxSpeed;
    bool delayed;
    trainState state;
public:
    Trains(int iId, std::string iFromStation, std::string iToStation, int iDepTime, int iArrTime,
           double iMaxSpeed, std::string iWagons) :
            id(iId), fromStation(std::move(iFromStation)),
            toStation(std::move(iToStation)),
            depTime(iDepTime),
            delayedDepTime(iDepTime),
            delayedArrTime(iArrTime),
            delayedTime(0),
            arrTime(iArrTime),
            maxSpeed(iMaxSpeed),
            wagons(std::move(iWagons)),
            state(NOT_ASSEMBLED),
            delayed(false){}

    // Get functions
    int getId() const { return id; }
    trainState getTrainState() { return state; }
    bool getDelayed() { return delayed; }
    std::string getFromStation() { return fromStation; }
    std::string getToStation() { return toStation; }
    int getDepTime() const { return depTime; }
    int getDelayedDepTime() { return delayedDepTime; }
    int getArrTime() const { return arrTime; }
    int getDelayedArrTime() { return delayedArrTime; }
    int getDelayedTime() { return delayedTime; }
    std::string getWagons() { return wagons; }
    double getMaxSpeed() { return maxSpeed; }

    // Set functions
    void setTrainState(trainState iState) { state = iState; }
    void setDelayed(bool iDelayed) { delayed = iDelayed; }
    void setDelayedDepTime(int iDelayedDepTime) { delayedDepTime = iDelayedDepTime; }
    void setDelayedArrTime(int iDelayedArrTime) { delayedArrTime = iDelayedArrTime; }
    void setDelayedTime(int iDelayedTime) { delayedTime = iDelayedTime; }

    // Prints type names of wagons
    void wagonPrint(std::string wagons);
};

#endif //OO_PROJEKT2019_DEL1_TRAINS_H
