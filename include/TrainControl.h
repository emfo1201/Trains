//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-30
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_TRAINCONTROLL_H
#define OO_PROJEKT2019_TRAINCONTROLL_H

#include "Constants.h"
#include "Carriage.h"
#include "CarriageGoodsWagon.h"
#include "CarriageGoodsWagonCovered.h"
#include "CarriageGoodsWagonOpen.h"
#include "CarriagePassengerCar.h"
#include "CarriagePassengerCarCoach.h"
#include "CarriagePassengerCarSleep.h"
#include "Locomotive.h"
#include "LocomotiveDiesel.h"
#include "LocomotiveElectric.h"
#include "Vehicle.h"
#include "Trains.h"
#include "Station.h"
#include <memory>
#include <vector>
#include <map>

// Forward declaration
class Simulation;

class TrainControl {
private:
    Simulation *theSim;
    int intervalTime, delayedTime, startTime, endTime, simTime;
    std::string loglevel, outputFile = "Trainsim.log";
    const char DELIM = ':';
    std::vector<std::unique_ptr<Station>> distance;
    std::vector<std::unique_ptr<Trains>> trains;
    //
    std::vector<std::string> trainStationValues;
    // All available wagons sorted by station
    std::multimap<std::string, std::unique_ptr<Vehicle>> vehiclePool;
    //All assemble trains
    std::multimap<int, std::unique_ptr<Vehicle>> trainPool;
    // To follow the train states, I add a string to a map.
    std::multimap<int, std::string> route;
    std::multimap<int, std::string> vehicleRoute;

public:
    explicit TrainControl(Simulation *sim)
            : theSim(sim), intervalTime(10), startTime(0), endTime(1439), delayedTime(0), simTime(0), loglevel("Low")
    { }
    ~TrainControl() { delete theSim; }
    // Function to change log level (low, normal or high)
    std::string changeLevel(std::string &level);
    // Function to change the time (start time, end time, interval time)
    std::string changeTime(std::string &time);
    // Function to change the arrival time when a train is delayed
    int changeArrTime(int id);
    // Function to convert time from a string (hh:mm) to an int
    int convertTime(std::string time);
    // Function to convert time from an int to a string (hh:mm)
    std::string sConvertTime(int time);
    // Function to convert speed when a train is delayed and might go faster than scheduled to reduce the delay
    double convertSpeed(int id);
    // Function to convert vehicleType
    std::string convertType(std::string type);

    // Set functions
    void setIntervalTime(std::string time);
    void setStartTime(std::string time);
    void setEndTime(std::string time);
    void setLoglevel(std::string level);

    // Get functions
    int getIntervalTime() { return intervalTime; }
    int getStartTime() { return startTime; }
    int getEndTime() { return endTime; }
    std::string getLoglevel() { return loglevel; }

    ///////////////////////////////////////////////////////////////////
    // File functions
    ///////////////////////////////////////////////////////////////////
    bool readTrainStationFile(std::string fileName);
    bool readTrainsFile(std::string fileName);
    bool readTrainMapFile(std::string trainMapFileName);
    void writeToFile(std::string ss);

    ///////////////////////////////////////////////////////////////////
    // Train functions
    ///////////////////////////////////////////////////////////////////
    bool assembleTrain(int id);         // Function that tries to assemble a train
    bool tryAssembleAgain(int id);      // Function that tries to reassemble a train if it was delayed
    bool addWagons(int id, std::string wagons, std::string stationName);    // Function that adds the wagons to the train
    void unloadWagons(int id, std::string stationName);     // Function that unloads the wagons
    // Print functions for different train states
    void printAssembled(int id, int time);
    void ready(int id, int time);
    int running(int id, int time);
    void arrived(int id, int time);
    void finished(int id, int time);
    void incomplete(int id, int time);
    // Function that converts the train states from int to string
    std::string convertState(trainState state);

    ///////////////////////////////////////////////////////////////////
    // Train Menu Functions
    ///////////////////////////////////////////////////////////////////
    void showTrainByNumber(int num);    // Print info of one train (by train id)
    void showTrainByVehicle(int id);    // Print info of one train (by vehicle id)
    void showTrainSchedule();           // Print train schedule
    void showAllTrains();               // Print info of all trains

    ///////////////////////////////////////////////////////////////////
    // Station Menu Functions
    ///////////////////////////////////////////////////////////////////
    void showStationNames();            // Print names of all stations
    void showStationByName(std::string stationName);     // Print available trains and vehicles at one station
    void showAllStations();             // Print available trains and vehicles at all stations

    ///////////////////////////////////////////////////////////////////
    // Vehicle Menu Functions
    ///////////////////////////////////////////////////////////////////
    void showVehicleById(int id);       // Print info of one vehicle
    void showAllVehicles();             // Print info of all vehicles


    ///////////////////////////////////////////////////////////////////
    // Statistics Menu Functions
    ///////////////////////////////////////////////////////////////////
    void printStatistics();             // Print statistics when simulation is finished
};
#endif //OO_PROJEKT2019_TRAINCONTROLL_H
