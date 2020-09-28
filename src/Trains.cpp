//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-26
//------------------------------------------------------------------------------

#include "../include/Trains.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
 * Prints type name for the wagons attached to a train
 * @param wagons
 */
void Trains::wagonPrint(string wagons){
    string type;
    vector<string> tmp;
    size_t p = wagons.find_first_not_of(' '); // Make sure the string does not start with a white space
    wagons.erase(0, p);
    stringstream line(wagons);

    // Push back all the values to a vector
    while(getline(line, type, ' ')){
        tmp.push_back(type);
    }
    // Loop the vector and print the wagon types
    for(auto&idx : tmp) {
        if (idx == "0")
            cout << "Passenger car, coach" << endl;
        if (idx == "1")
            cout << "Passenger car, sleep" << endl;
        if (idx == "2")
            cout << "Open goods wagon" << endl;
        if (idx == "3")
            cout << "Covered goods wagon" << endl;
        if (idx == "4")
            cout << "Electric locomotive" << endl;
        if (idx == "5")
            cout << "Diesel locomotive" << endl;
    }
}