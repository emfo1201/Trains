//------------------------------------------------------------------------------
// UserInterface.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-26
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_USERINTERFACE_H
#define OO_PROJEKT2019_USERINTERFACE_H

#include "Event.h"
#include "Simulation.h"
#include "TrainControl.h"
#include <iostream>
#include <string>

class UserInterface {
private:
    Simulation *theSim;
    TrainControl *TC;
public:
    UserInterface() : theSim(new Simulation), TC(new TrainControl(theSim)) {}
    ~UserInterface() { delete theSim; delete TC; }
    // Function for reading file
    bool readFile(std::string trainStationFileName, std::string trainsFileName, std::string trainMapFileName);
    // Function to change log level (low, normal or high)
    std::string changeLevel(std::string &level);
    // Function to change the time (start time, end time, interval time)
    std::string changeTime(std::string &time);
    // Function to set interval time
    void setIntervalTime(std::string time);
    // Function to set start time
    void setStartTime(std::string time);
    // Function to set end time
    void setEndTime(std::string time);
    // Function to set log level
    void setLoglevel(std::string level);

    ///////////////////////////////////////////////////////////////////
    // Simulation Menu Functions
    ///////////////////////////////////////////////////////////////////
    void runNextInterval();         // Function to run next interval
    void nextEvent();               // Function to run next event
    void runSim();                  // Function to run whole simulation

    ///////////////////////////////////////////////////////////////////
    // Train Menu Functions
    ///////////////////////////////////////////////////////////////////
    void showTrainByNumber();       // Print info of one train (by train id)
    void showTrainByVehicle();      // Print info of one train (by vehicle id)
    void showTrainSchedule();       // Print train schedule
    void showAllTrains();           // Print info of all trains
    ///////////////////////////////////////////////////////////////////
    // Station Menu Functions
    ///////////////////////////////////////////////////////////////////
    void showStationNames();        // Print names of all stations
    void showStationByName();       // Print available trains and vehicles at one station
    void showAllStations();         // Print available trains and vehicles at all stations
    ///////////////////////////////////////////////////////////////////
    // Vehicle Menu Functions
    ///////////////////////////////////////////////////////////////////
    void showVehicleById();         // Print info of one vehicle
    void showAllVehicles();         // Print info of all vehicles
    ///////////////////////////////////////////////////////////////////
    // Statistics Menu Functions
    ///////////////////////////////////////////////////////////////////
    void printStatistics();         // Print statistics when simulation is finished
};

#endif //OO_PROJEKT2019_USERINTERFACE_H
