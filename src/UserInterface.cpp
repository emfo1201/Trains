//------------------------------------------------------------------------------
// UserInterface.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-26
//------------------------------------------------------------------------------

#include "../include/UserInterface.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * Function that calls all reading file funtions and returns true if possible to read all files.
 * @param trainStationFileName
 * @param trainsFileName
 * @param trainMapFileName
 * @return true if possible to read all files
 */
bool UserInterface::readFile(string trainStationFileName, string trainsFileName, string trainMapFileName){
    // Try read in files and when reading in trainsFileName, schedule all events
    try{
        if(TC->readTrainStationFile(std::move(trainStationFileName))&&
           TC->readTrainsFile(std::move(trainsFileName)) &&
           TC->readTrainMapFile(std::move(trainMapFileName)))
            return true;
    }catch(runtime_error &error){
        cout << "Error: " << error.what() << endl;
    }
    return false;
}

std::string UserInterface::changeLevel(string &level){
    return TC->changeLevel(level);
}
std::string UserInterface::changeTime(string &time){
    return TC->changeTime(time);
}

void UserInterface::setIntervalTime(string time){
    TC->setIntervalTime(move(time));
}

void UserInterface::setStartTime(string time){
    TC->setStartTime(move(time));
}
void UserInterface::setEndTime(string time){
    TC->setEndTime(move(time));
}

void UserInterface::setLoglevel(std::string level) {
    TC->setLoglevel(level);
}

///////////////////////////////////////////////////////////////////
// Simulation Menu Functions
///////////////////////////////////////////////////////////////////

/**
 * Funciton that runs next interval. The user can change the interval time in the menu.
 */
void UserInterface::runNextInterval(){
    bool again = true;
    int time = TC->getIntervalTime();
    char input = 'n';
    do{
        stringstream ss;
        ss << "Current time: [" << TC->sConvertTime(theSim->getTime()) << "]";
        cout << ss.str() << endl;
        TC->writeToFile(ss.str());
        if(theSim->runInterval(time)){
            cout << "Do you want to continue to next interval (Y/N) ";
            cin >> input;
        }
        else{
            cout << endl << "End of simulation. Details: " << endl << endl;
            printStatistics();
            again = false;
        }
        if(input == 'n' || input == 'N')
            again = false;
    }while(again);

}

/**
 * Function that runs the next event in the event queue.
 */
void UserInterface::nextEvent() {
    bool again = true;
    char input = 'n';
    do{
        stringstream ss;
        ss << "(Next event)";
        cout << ss.str() << endl;
        TC->writeToFile(ss.str());
        if(theSim->runNextEvent()) {
            cout << "Do you want to continue to next event (Y/N) ";
            cin >> input;
        }
        else{
            cout << "End of simulation. Details: " << endl << endl;
            printStatistics();
            again = false;
        }

        if(input == 'n' || input == 'N')
            again = false;
    }while(again);
}

/**
 * Function that runs the whole simulation
 */
void UserInterface::runSim(){
    stringstream ss;
    ss << "(Run simulation) start time: [" << TC->sConvertTime(theSim->getTime() + TC->getIntervalTime()) << "]";
    cout << ss.str() << endl;
    TC->writeToFile(ss.str());
    theSim->runAll();
    cout << endl << endl << "End of simulation. Details: " << endl << endl;
    TC->printStatistics();
}

///////////////////////////////////////////////////////////////////
// Station Menu Functions
///////////////////////////////////////////////////////////////////

/**
 * Show all the log changes for one train
 */
void UserInterface::showTrainByNumber(){
    cout << "Enter ID of train you want to show: ";
    int id;
    cin >> id;
    TC->showTrainByNumber(id);
}

/**
 * Show all the log changes for one vehicle
 */
void UserInterface::showTrainByVehicle(){
    cout << "Enter ID of vehicle you want to show: ";
    int id;
    cin >> id;
    TC->showTrainByVehicle(id);
}

/**
 * Function that prints the train schedule
 */
void UserInterface::showTrainSchedule(){
    cout << "Train schedule: " << endl << endl;
    TC->showTrainSchedule();
}

/**
 * Show info for all trains
 */
void UserInterface::showAllTrains(){
    TC->showAllTrains();
}

///////////////////////////////////////////////////////////////////
// Station Menu Functions
///////////////////////////////////////////////////////////////////

/**
 * Function that prints all the names of the stations
 */
void UserInterface::showStationNames() {
    cout << "All station names:" << endl;
    TC->showStationNames();
}

/**
 * Function that prints all the vehicles and trains available at one station
 */
void UserInterface::showStationByName() {

    cout << "Available stations: " << endl;
    TC->showStationNames();
    cout << endl << endl << "What station do you want to show info about: ";
    string station;
    getline(cin, station);
    TC->showStationByName(station);
}

/**
 * Function that prints all the vehicles and trains available at all stations
 */
void UserInterface::showAllStations() {
    TC->showAllStations();
}

///////////////////////////////////////////////////////////////////
// Vehicle Menu Functions
///////////////////////////////////////////////////////////////////

/**
 * Function that prints the info of one vehicle
 */
void UserInterface::showVehicleById(){
    cout << "Choose ID of the vehicle you wish to show: ";
    int id;
    cin >> id;
    TC->showVehicleById(id);
}

/**
 * Function that prints all info of all vehicles
 */
void UserInterface::showAllVehicles(){
    cout << "All vehicles in the pool" << endl;
    TC->showAllVehicles();
}


///////////////////////////////////////////////////////////////////
// Statistics Menu Functions
///////////////////////////////////////////////////////////////////

void UserInterface::printStatistics(){
    TC->printStatistics();
}

