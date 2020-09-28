//------------------------------------------------------------------------------
// Menu.h DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-26
//------------------------------------------------------------------------------

#include "../include/Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

/**
 * First function that runs when starting the application. If possible to read all files,
 * create Trainsim.log, if not exist, or clear the file, if it exists and after that,
 * start the menu system.
 */
void Menu::run(){

    if(UI.readFile("TrainStations.txt", "Trains.txt", "TrainMap.txt")){
        try{
            ofstream ofs;
            ofs.open("Trainsim.log", ofstream::in | ofstream::out | ofstream::trunc);
            ofs.close();
        }catch(runtime_error &error){
            cout << "Error: " << error.what() << endl;
        }


        startMenuOptions();
    }
    else{
        cout << "At least one of the files doesn't exist. Please make sure all the files"
                " exists and try run the program again" << endl;
    }
}


/**
 * Function that prints the start menu.
 */
void Menu::startMenu()							// Menu options
{
    vector<string> menu;                            // A vector, holding the menu choices

    string startTime ="1. Change start time [";
    startTime.append(start);
    startTime.append(end);
    string endTime ="2. Change end time [";
    endTime.append(stop);
    endTime.append(end);
    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    menu.emplace_back("                           Start menu ");
    menu.emplace_back("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    menu.emplace_back(" ");
    menu.emplace_back(startTime);
    menu.emplace_back(endTime);
    menu.emplace_back("3. Start simulation");
    menu.emplace_back("0. Exit");

    // Print menu text
    for (auto const &i : menu) {
        cout << i << endl;
    }
}

/**
 * Function that handles the menu input from the user.
 */
void Menu::startMenuOptions() {
    bool again = true;
    do {
        startMenu();                    // Show menu
        int choice;
        cout << endl << "Choice: ";
        cin >> choice;                    // Menu choice prompt

        // If input is incorrect, prompt the user to try again.
        while(cin.fail() || choice < 0 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Bad entry, Choice: ";
            cin >> choice;
        }
        cin.get();

        switch (choice)                                // Menu choices
        {
            case 1:
                UI.changeTime(start);
                UI.setStartTime(start);
                break;
            case 2:
                UI.changeTime(stop);
                UI.setEndTime(stop);
                break;
            case 3:
                simulationMenuOptions();
                break;
            default: again = false;
        }
    }while (again);
}

/**
 * Function that prints the simulation menu
 */
void Menu::simulationMenu(){
    vector<string> menu;                            // A vector, holding the menu choices

    string startTime ="1. Change interval [";
    startTime.append(interval);
    startTime.append(end);
    string changeLogLevel ="5. Change log level [";
    changeLogLevel.append(level);
    changeLogLevel.append(end);
    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    menu.emplace_back("                           Simulation menu ");
    menu.emplace_back("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    menu.emplace_back(" ");
    menu.emplace_back(startTime);
    menu.emplace_back("2. Run next interval");
    menu.emplace_back("3. Next event");
    menu.emplace_back("4. Finish (Complete simulation)");
    menu.emplace_back(changeLogLevel);
    menu.emplace_back("6. Train menu");
    menu.emplace_back("7. Station menu");
    menu.emplace_back("8. Vehicle menu");
    menu.emplace_back("0. Return");

    // Print menu text
    for (auto const &i : menu) {
        cout << i << endl;
    }
}

/**
 * Function that handles the menu input from the user.
 */
void Menu::simulationMenuOptions(){
    bool again = true;

    do {
        simulationMenu();                   // Show menu
        int choice;
        cout << endl << "Choice: ";
        cin >> choice;                    // Menu choice prompt

        // If input is incorrect, prompt the user to try again.
        while(cin.fail() || choice < 0 || choice > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Bad entry, Choice: ";
            cin >> choice;
        }
        cin.get();


        switch (choice)                                // Menu choices
        {
            case 1:
                UI.changeTime(interval);
                UI.setIntervalTime(interval);
                break;
            case 2:
                UI.runNextInterval();
                break;
            case 3:
                UI.nextEvent();
                break;
            case 4:
                UI.runSim();
                break;
            case 5:
                UI.changeLevel(level);
                UI.setLoglevel(level);
                break;
            case 6:
                trainMenuOptions();
                break;
            case 7:
                stationMenuOptions();
                break;
            case 8:
                vehicleMenuOptions();
                break;
            default: again = false;
        }
    }while (again);
}


/**
 * Function that prints the train menu
 */
void Menu::trainMenu(){
    vector<string> menu;                            // A vector, holding the menu choices

    string changeLogLevel ="5. Change log level [";
    changeLogLevel.append(level);
    changeLogLevel.append(end);
    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    menu.emplace_back("                           Train menu ");
    menu.emplace_back("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    menu.emplace_back(" ");
    menu.emplace_back("1. Search train by number");
    menu.emplace_back("2. Search train by vehicle id");
    menu.emplace_back("3. Show all trains");
    menu.emplace_back("3. Show train schedule");
    menu.emplace_back(changeLogLevel);
    menu.emplace_back("0. Return");

    // Print menu text
    for (auto const &i : menu) {
        cout << i << endl;
    }
}


/**
 * Function that handles the menu input from the user.
 */
void Menu::trainMenuOptions(){
    bool again = true;

    do {
        trainMenu();                   // Show menu
        int choice;
        cout << endl << "Choice: ";
        cin >> choice;                    // Menu choice prompt

        // If input is incorrect, prompt the user to try again.
        while(cin.fail() || choice < 0 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Bad entry, Choice: ";
            cin >> choice;
        }
        cin.get();


        switch (choice)                                // Menu choices
        {
            case 1:
                UI.showTrainByNumber();
                break;
            case 2:
                UI.showTrainByVehicle();
                break;
            case 3:
                UI.showAllTrains();
                break;
            case 4:
                UI.showTrainSchedule();
            case 5:
                UI.changeLevel(level);
                UI.setLoglevel(level);
                break;
            default: again = false;
        }
    }while (again);
}


/**
 * Function that prints the station menu
 */
void Menu::stationMenu(){
    vector<string> menu;                            // A vector, holding the menu choices

    string changeLogLevel ="4. Change log level [";
    changeLogLevel.append(level);
    changeLogLevel.append(end);
    cout << endl << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    menu.emplace_back("                           Station menu ");
    menu.emplace_back("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    menu.emplace_back(" ");
    menu.emplace_back("1. Show station names");
    menu.emplace_back("2. Show station by name");
    menu.emplace_back("3. Show all stations");
    menu.emplace_back(changeLogLevel);
    menu.emplace_back("0. Return");

    // Print menu text
    for (auto const &i : menu) {
        cout << i << endl;
    }
}

/**
 * Function that handles the menu input from the user.
 */
void Menu::stationMenuOptions(){
    bool again = true;

    do {
        stationMenu();                   // Show menu
        int choice;
        cout << endl << "Choice: ";
        cin >> choice;                    // Menu choice prompt

        // If input is incorrect, prompt the user to try again.
        while(cin.fail() || choice < 0 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Bad entry, Choice: ";
            cin >> choice;
        }
        cin.get();


        switch (choice)                                // Menu choices
        {
            case 1:
                UI.showStationNames();
                break;
            case 2:
                UI.showStationByName();
                break;
            case 3:
                UI.showAllStations();
                break;
            case 4:
                UI.changeLevel(level);
                UI.setLoglevel(level);
                break;
            default: again = false;
        }
    }while (again);
}


/**
 * Function that prints the vehicle menu
 */
void Menu::vehicleMenu(){
    vector<string> menu;                            // A vector, holding the menu choices

    string changeLogLevel ="3. Change log level [";
    changeLogLevel.append(level);
    changeLogLevel.append(end);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    menu.emplace_back("                           Vehicle menu ");
    menu.emplace_back("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    menu.emplace_back(" ");
    menu.emplace_back("1. Show vehicle by id");
    menu.emplace_back("2. Show all vehicles");
    menu.emplace_back(changeLogLevel);
    menu.emplace_back("0. Return");

    // Print menu text
    for (auto const &i : menu) {
        cout << i << endl;
    }
}

/**
 * Function that handles the menu input from the user.
 */
void Menu::vehicleMenuOptions(){
    bool again = true;

    do {
        vehicleMenu();                   // Show menu
        int choice;
        cout << endl << "Choice: ";
        cin >> choice;                    // Menu choice prompt

        // If input is incorrect, prompt the user to try again.
        while(cin.fail() || choice < 0 || choice > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Bad entry, Choice: ";
            cin >> choice;
        }
        cin.get();

        switch (choice)                                // Menu choices
        {
            case 1:
                UI.showVehicleById();
                break;
            case 2:
                UI.showAllVehicles();
                break;
            case 3:
                UI.changeLevel(level);
                UI.setLoglevel(level);
                break;
            default: again = false;
        }
    }while (again);
}