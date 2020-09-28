//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-26
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_MENU_H
#define OO_PROJEKT2019_MENU_H

#include "../include/UserInterface.h"
#include <iostream>

class Menu {
private:
    UserInterface UI;
    std::string level;
    std::string start;
    std::string stop;
    std::string interval;
    std::string simTime;
    const std::string end = "]";

    // Menu functions, for printing menu options and for handle input from user
    void startMenu();
    void simulationMenuOptions();
    void simulationMenu();
    void trainMenuOptions();
    void trainMenu();
    void stationMenu();
    void stationMenuOptions();
    void vehicleMenu();
    void vehicleMenuOptions();
    void startMenuOptions();
public:
    Menu() : level("Low"), start("00:00"), stop("23:59"), interval("00:10"), simTime("00:00"){}
    // Run the program. First function to be called when running application
    void run();

};

#endif //OO_PROJEKT2019_MENU_H
