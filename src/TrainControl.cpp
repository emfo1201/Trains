//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-30
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <locale>
#include "../include/TrainControl.h"
#include "../include/Simulation.h"

using namespace std;

/**
 * Function that changes the log level of the simulation.
 * @param level the old level
 * @return the new level
 */
string TrainControl::changeLevel(string &level){
    cout << "Change level: " << endl;
    cout << "1. Low level" << endl;
    cout << "2. Normal level" << endl;
    cout << "3. High level" << endl;
    cout << "0. Return" << endl;
    cout << "Choice: ";
    int choice;
    cin >> choice;
    // Input validation
    while(cin.fail() || choice < 0 || choice > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Bad entry, Choice: ";
        cin >> choice;
    }
    cin.get();
    switch(choice){
        case 1:
            level = "Low";
            break;
        case 2:
            level = "Normal";
            break;
        case 3:
            level = "High";
            break;
        default:
            break;
    }
    return level;
}

/**
 * Function that changes the time. StartTime, EndTime and interval
 * @param time current time
 * @return new time
 */
string TrainControl::changeTime(string &time){
    int startHour;
    int startMinute;
    char colon = ':';
    cout << "Change time from " << time << " to (hh:mm): ";
    cin >> startHour >> colon >> startMinute;

    string hour = to_string(startHour);
    string minute = to_string(startMinute);

    // If bad input, return the old time and inform the user about the misshap
    if(cin.fail() || startHour < 0 || startHour > 23 || startMinute < 0 || startMinute > 59)
    {
        cout << "Invalid input. Input should be in format hh:mm and between 00:00 and 23:59" << endl;
        return time;
    }

    // Create a stringstream of format hh:mm and return that as a string
    ostringstream ss;
    ss << setw(2) << setfill('0') << hour << DELIM << setw(2) << setfill('0') << minute;
    time = ss.str();

    return time;
}

/**
 * Function that changes the arrival time when a train is running late
 * @param id The id of the train
 * @return the new arrival time
 */
int TrainControl::changeArrTime(int id){
    double speed, dist = 0, arrTime = 0;

    // Function that returns the speed a train needs to hold to get to the arrival station on time
    speed = convertSpeed(id);

    for (auto &idx : trains) {
        if (idx && idx->getId() == id) {
            if(idx->getMaxSpeed() > speed){
                speed = idx->getMaxSpeed();
                // find the distance between departure station and arrival station
                for (auto &i : distance) {
                    if (i && ((i->getStation1() == idx->getFromStation() && i->getStation2() == idx->getToStation()) ||
                              (i->getStation2() == idx->getFromStation() && i->getStation1() == idx->getToStation()))) {
                        dist = i->getDistance();
                        // The new arrival time for the train.
                        arrTime = ((dist / speed) * 60) + idx->getDelayedDepTime();
                        // If the new arrTime happens to be sooner than the original arrTime, return the org. arrTime
                        if(arrTime <= idx->getArrTime()){
                            arrTime = idx->getArrTime();
                        }

                        break;
                    }
                }
            }
            else{
                 arrTime = idx->getArrTime();
                 break;
            }
        }
    }
    return (int) arrTime;
}

 /**
  * Function that converts time from string to int
  * @param time as a string
  * @return as an int
  */
int TrainControl::convertTime(std::string time) {
    int convTime;
    stringstream intTime(time);
    string minutes;
    getline(intTime, minutes, DELIM);
    convTime = stoi(minutes) * 60;
    getline(intTime, minutes);
    return convTime += stoi(minutes);
}

/**
 * Function that converts time from int to string
 * @param time as an int
 * @return as a string
 */
string TrainControl::sConvertTime(int time){
    string convTime;
    int minutes = 0, hour = 0, day = 0;

    minutes = time%60;
    hour = time/60;
    ostringstream ss;

    if(hour >= 24){
        day = hour/24;
        hour = hour%24;
        ss << setw(2) << setfill('0') << to_string(day) << DELIM << setw(2) << setfill('0') << to_string(hour) << DELIM << setw(2) << setfill('0') << to_string(minutes);
    }else{
        ss << setw(2) << setfill('0') << to_string(hour) << DELIM << setw(2) << setfill('0') << to_string(minutes);
    }

    convTime = ss.str();
    return convTime;
}

/**
 * Function that converts speed.
 * @param id of the train
 * @return the new speed
 */
double TrainControl::convertSpeed(int id) {
    double speed = 0, dist = 0, tid = 0;
    for (auto &idx : trains) {
        if (idx && idx->getId() == id) {
            // Find the distance between departure station and arrival station
            for (auto &i : distance) {
                if (i && ((i->getStation1() == idx->getFromStation() && i->getStation2() == idx->getToStation()) ||
                          (i->getStation2() == idx->getFromStation() && i->getStation1() == idx->getToStation()))) {
                    dist = i->getDistance();
                    // The time it takes to run between stations
                    tid = ((double)idx->getDelayedArrTime() - (double)idx->getDelayedDepTime()) / 60;
                    // Speed is the difference between distance and time
                    speed = (dist / tid);
                    // If speed is higher than the maximum speed of the train, return getMaxSpeed instead
                    if(speed > idx->getMaxSpeed())
                        speed = idx->getMaxSpeed();
                    break;
                }
            }

        }
    }
    return speed;
}

/**
 * Function that converts carType to readable type
 * @param type type of wagon (0-5)
 * @return type as a readable string
 */
string TrainControl::convertType(string type){
    string carType;
    if (type == "0")
        carType = "Passenger car, coach";
    if (type == "1")
        carType = "Passenger car, sleep";
    if (type == "2")
        carType = "Open goods wagon";
    if (type == "3")
        carType = "Covered goods wagon";
    if (type == "4")
        carType = "Electric locomotive";
    if (type == "5")
        carType = "Diesel locomotive";
    return carType;
}

/**
 * Set function for interval time
 * @param time
 */
void TrainControl::setIntervalTime(std::string time){
    intervalTime = convertTime(move(time));
}

/**
 * Set function for start time
 * @param time
 */
void TrainControl::setStartTime(std::string time){
    startTime = convertTime(move(time));
    theSim->setTime(startTime);
}

/**
 * Set function for end time
 * @param time
 */
void TrainControl::setEndTime(std::string time){
    endTime = convertTime(move(time));
}

/**
 * Set function for log level
 * @param level
 */
void TrainControl::setLoglevel(std::string level) {
    loglevel = move(level);
}

///////////////////////////////////////////////////////////////////
// Simulation Menu Functions
///////////////////////////////////////////////////////////////////


/**
 * Function that reads the train station file
 * @param fileName
 * @return true if possible to read file
 */
bool TrainControl::readTrainStationFile(string fileName) {
    ifstream file(fileName, ios::in);

    if (file.is_open()) {
        string str, station, type, value1, value2, value3;
        // Read file and push back line by line.
        while (getline(file, str)) {
            trainStationValues.push_back(str);
        }
        file.close(); // Close file
        // Split the lines in the trainStationValues-vector and push back every
        // value to a new vector. In trainStationVector, every index contains the
        // station name and all the wagons at the station. By splitting the lines
        // and push back to tmpVehicleValues, we get station in one index and all the
        // wagons in different indexes. One wagon per index.
        vector<string> tmpVehicleValues;
        for (auto &idx : trainStationValues) {
            stringstream ss(idx);
            while (getline(ss, str, '(')) {
                str.erase(remove(str.begin(), str.end(), ')'), str.end());
                tmpVehicleValues.push_back(str);
            }
        }
        // Done using the trainStationValues vector, we clear it, to be able to reuse it for another purpose
        trainStationValues.clear();

        // Now that we have all the values separated, we are able to insert them into a map. All wagons are
        // associated with one station (station is key, wagons is value)
        for (auto &idx : tmpVehicleValues) {
            // Check if the value in index is digit or string. If value is string (station), make it a key,
            // otherwise, find the second value in the string and make that a type.
            if (any_of(idx.begin(), idx.end(), ::isdigit)) {
                istringstream stream(idx);
                auto start = idx.find_first_of(' ', 0);
                auto end = idx.find_first_of(' ', start + 1);
                type = idx.substr(start, end - start);
                // Make sure the type is just the int and no white spaces.
                type.erase(std::remove(type.begin(), type.end(), ' '), type.end());

                if (type == "0") {
                    // Split the string and insert them to the multimap
                    stream >> value1 >> type >> value2 >> value3;
                    vehiclePool.insert(make_pair(station, new CarriagePassengerCarCoach(stoi(value1), stoi(value2),
                                                                                        stoi(value3))));
                }
                if (type == "1") {
                    stream >> value1 >> type >> value2;
                    vehiclePool.insert(
                            make_pair(station, new CarriagePassengerCarSleep(stoi(value1), stoi(value2))));
                }
                if (type == "2") {
                    stream >> value1 >> type >> value2 >> value3;
                    vehiclePool.insert(make_pair(station, new CarriageGoodsWagonOpen(stoi(value1), stoi(value2),
                                                                                     stoi(value3))));
                }
                if (type == "3") {
                    stream >> value1 >> type >> value2;
                    vehiclePool.insert(
                            make_pair(station, new CarriageGoodsWagonCovered(stoi(value1), stoi(value2))));
                }
                if (type == "4") {
                    stream >> value1 >> type >> value2 >> value3;
                    vehiclePool.insert(
                            make_pair(station, new LocomotiveElectric(stoi(value1), stoi(value2), stoi(value3))));
                }
                if (type == "5") {
                    stream >> value1 >> type >> value2 >> value3;
                    vehiclePool.insert(
                            make_pair(station, new LocomotiveDiesel(stoi(value1), stoi(value2), stoi(value3))));
                }
            } else {
                station = idx;
                station.erase(station.find_last_not_of(' ') + 1);
            }

        }
        // Clear the tmpVehicleValues vector to not use any memory, because we dont need it anymore
        tmpVehicleValues.clear();
        // When all the values is in its right place, fill trainStationValues vector with the
        // start values for every station (station + number of wagons), to save for the statistics
        // output later.
        int count;
        for( auto idx = vehiclePool.begin(), end = vehiclePool.end();
             idx != end;
             idx = vehiclePool.upper_bound(idx->first)){
            auto p = vehiclePool.equal_range(idx->first);
            count = std::distance(p.first, p.second);
            string ss = idx->first + " = " + to_string(count);
            trainStationValues.push_back(ss);
        }
        return true;
    } else {
        cout << "Couldn't find file" << endl;
    }

    return false;
}

/**
 * Function that reads trains file
 * @param fileName
 * @return true if possible to read file
 */
bool TrainControl::readTrainsFile(string fileName){
    int id;
    double maxSpeed;
    string str, fromStation, toStation, depTime, arrTime, wagons, time1, time2;
    int iDepTime = 0, iArrTime = 0;
    ifstream file(fileName, ios::in);
    if (file.is_open()) {
        while (getline(file, str)) {
            stringstream line(str);

            // Read the first part of the line and assign
            line >> id >> fromStation >> toStation >> depTime >> arrTime >> maxSpeed;
            // Read last part of the line and assign to wagons (because of various number of wagons in a train
            getline(line, wagons);
            // Change time strings to int and convert string to int (time in minutes)
            iDepTime = convertTime(depTime);
            iArrTime = convertTime(arrTime);
            // Add all to trains vector
            trains.emplace_back(new Trains(id, fromStation, toStation, iDepTime, iArrTime, maxSpeed, wagons));
            //Add to scheduleEvent, to be able to run the simulation
            theSim->scheduleEvent(new AssembledEvent(theSim,this, (unsigned int) iDepTime - SCHEDULE_BUILD, id));
        }
        file.close();

        return true;
    }
    else{
        throw(runtime_error("Unable to open file."));
    }

//    return false;
}

/**
 * Function that reads trainmap file
 * @param fileName
 * @return true if possible to read file
 */
bool TrainControl::readTrainMapFile(std::string fileName){
    string station1, station2, dist;
    double distance1;
    string str;
    ifstream file(fileName, ios::in);
    if (file.is_open()) {
        while (getline(file, str)) {
            stringstream ss(str);
            ss >> station1 >> station2 >> dist;
            distance1 = stod(dist);
            distance.emplace_back(new Station(station1, station2, distance1));
        }
        file.close();
        return true;
    }
    else{
        throw(runtime_error("Unable to open file."));
    }
    return false;
}

/**
 * Write all log changes to file
 * @param ss - string with log info
 */

void TrainControl::writeToFile(string ss){
    ofstream ofs;
    ofs.open (outputFile, ofstream::out | ofstream::app);
    ofs << ss << endl;
    ofs.close();
}

/**
 * Function that assemble trains.
 * @param id of train to assemble
 * @return true if possible to assemble train
 */
bool TrainControl::assembleTrain(int id) {

    for(auto &idx : trains){
        if(idx && idx->getId() == id){
            if(addWagons(id, idx->getWagons(), idx->getFromStation())) {
                idx->setTrainState(ASSEMBLED);
                return true;
            }
            else{
                idx->setTrainState(INCOMPLETE);
            }
            return false;
        }
    }
    return false;
}

/**
 * Function that tries to reassemble a train, if it has the incomplete state
 * @param id of the train
 * @return true if possible to assemble train
 */
bool TrainControl::tryAssembleAgain(int id){
    for(auto &idx : trains){
        if(idx && idx->getId() == id){
            // First unload the already attached wagons, because we want them in the right order
            unloadWagons(id, idx->getFromStation());
            // Try assemble train again
            if (assembleTrain(id)) {
                return true;
            }
            return false;
        }
    }
    return false;
}

/**
 * Function that adds wagons to the train
 * @param id the id of the train
 * @param wagons the wagons to be added
 * @param stationName the station name where the function needs to look for the wagons to attach
 * @return true if all wagons was found
 */
bool TrainControl::addWagons(int id, string wagons, string stationName) {
    bool success = true;
    string carType, type;
    int i = 0;
    vector<string> tmp;

    // Split the wagon string to find out what wagons need to be found
    size_t p = wagons.find_first_not_of(' ');
    wagons.erase(0, p);
    stringstream line(wagons);
    while(getline(line, type, ' ')){
        tmp.push_back(type);
    }
    for(auto &idx : tmp) {
        carType = convertType(idx);

        // Make sure the wagon with lowest id always is the chosen one
        auto v = vehiclePool.equal_range(stationName);
        int value = 10000;
        for (auto it = v.first; it != v.second; ++it) {
            if (it->second->carType() == carType) {
                if (value > it->second->getId())
                    value = it->second->getId();
            }
        }
        // Search the station for wagons
        for (auto it = vehiclePool.find(stationName); it != vehiclePool.end(); it++){
            if (it->second->getId() == value) {
                // If wagon is found, add wagon to trainPool and delete from vehiclePool
                trainPool.insert(make_pair(id, move(it->second)));
                vehiclePool.erase(it);
                success = true;
                break;
            }
            success = false;
        }
        // If wagon was found, increase i and if i is the same size as tmp, then all wagons was found
        if(success){
            i++;
        }
    }
    tmp.size();
    if(i != tmp.size()){
        success = false;
    }
    tmp.clear();
    return success;
}

/**
 * Function to unload wagons from train
 * @param id of train
 * @param stationName station to unload at
 */
void TrainControl::unloadWagons(int id, string stationName){
    // Find train matching id and push back the car types to a tmp vector
    auto p = trainPool.equal_range(id);
    vector <string> type;
    for (auto it = p.first; it != p.second; ++it) {
        type.push_back(it->second->carType());
    }

    // Search the tmp vector and when carType matches the value of wagon attached to the train
    // insert wagon to vehiclePool and deletefrom trainPool.
    // I did this solution because I could not find a way to loop through trainPool directly
    // and insert wagons to vehiclePool and delete from trainPool without breaking the loop.
    // When I tried that, I got a segmentation fault. I guess it's possible to do this in a
    // much better way, but at the moment I haven't figured it out.
    for(auto &idx : type)
    {
        auto b = trainPool.equal_range(id);
        for (auto it = b.first; it != b.second; ++it) {
            if(it->second->carType() == idx) {
                vehiclePool.insert(make_pair(stationName, move(it->second)));
                trainPool.erase(it);
                break;
            }
        }
    }
}

/**
 * Function that handles the assembled state and prints info to screen.
 * The print to screen differ depending on log level
 * @param id of the train
 * @param time simulation time
 */
void TrainControl::printAssembled(int id, int time){
        for(auto &idx : trains){
            if(idx && idx->getId() == id){
                if(idx->getDelayed()) {     // If train is delayed, set the delayedTime and change delayed arr time
                    delayedTime += idx->getDelayedTime();
                    idx->setDelayedArrTime(changeArrTime(id));
                }
                if(time >= getStartTime()) { // If time is higher than start time, print to screen
                    stringstream ss;
                    ss << sConvertTime(time) << " Train [" << idx->getId() << "]";
                    if (getLoglevel() == "Normal" || getLoglevel() == "High") {
                        ss << " (" << convertState(idx->getTrainState()) << ") from "
                           << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << " ("
                           << sConvertTime(idx->getDelayedDepTime()) << ") to "
                           << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << " ("
                           << sConvertTime(idx->getDelayedArrTime()) << ") delay ("
                           << sConvertTime(idx->getDelayedTime()) << ") speed = 0 km/h";
                    }
                    ss << " is now assembled";
                    if (getLoglevel() == "Normal" || getLoglevel() == "High") {
                        ss << " , arriving at the platform at " << sConvertTime(idx->getArrTime()) << " ("
                           << sConvertTime(idx->getDelayedArrTime()) << ")";
                    }
                    // Loop through trainPool and add a string with info about vehcile, to vehicleRoute multimap.
                    // and a string with info about train to route multimap.
                    int vehicleId;
                    auto it = trainPool.equal_range(idx->getId());
                    for (auto x = it.first; x != it.second; ++x) {
                        stringstream xs;
                        vehicleId = x->second->getId();
                        xs << sConvertTime(time) << " [" << x->second->carType() << "] " << x->second->printing()
                           << endl
                           << " is now a part of train [" << idx->getId()
                           << "] " << convertState(idx->getTrainState()) << " from " << idx->getFromStation() << " ("
                           << sConvertTime(idx->getDelayedDepTime()) << " to " << idx->getToStation() << " ("
                           << sConvertTime(idx->getDelayedArrTime())
                           << ") delay (" << sConvertTime(idx->getDelayedTime()) << ")" << endl;
                        // If log level is high, print info about the wagons to screen
                        if (getLoglevel() == "High") {
                            ss << endl << " [" << x->second->carType() << "] ID: " << x->second->getId() << ", "
                               << x->second->printing();
                        }
                        vehicleRoute.insert(make_pair(vehicleId, xs.str())); // insert vehicle string to vehicleRoute
                    }

                    cout << ss.str() << endl;   // Print train info to screen
                    writeToFile(ss.str());      // Write train info to file
                    route.insert(make_pair(id, ss.str()));  // Insert train info to route multimap
                }
                break;
            }
    }
}

/**
 * Function that handles the ready state and prints info to screen.
 * The print to screen differ depending on log level
 * @param id of the train
 * @param time simulation time
 */
void TrainControl::ready(int id, int time){
    for(auto &idx : trains){
        if(idx && idx->getId() == id){
            idx->setTrainState(READY); // Set train state READY
            if(time >= getStartTime()) { // Print to screen if time is higher than start time
                 stringstream ss;
                ss << sConvertTime(time) << " Train [" << idx->getId() << "]";
                // If log level is normal or high, print mor than just train and id
                if(getLoglevel() == "Normal" || getLoglevel() == "High"){
                    ss << " (" << convertState(idx->getTrainState()) << ") from "
                       << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << " (" << sConvertTime(idx->getDelayedDepTime()) << ") to "
                       << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(idx->getDelayedArrTime()) << ") delay ("
                       << sConvertTime(idx->getDelayedTime()) << ") speed = 0 km/h";
                }
                ss << " is now ready";
                if(getLoglevel() == "Normal" || getLoglevel() == "High") {
                    ss << ", arriving at the platform at "
                       << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(idx->getDelayedArrTime()) << ")";
                }
                // For info, se printAssembled
                int vehicleId;
                auto it = trainPool.equal_range(idx->getId());
                for (auto x = it.first; x != it.second; ++x) {
                    stringstream xs;
                    vehicleId = x->second->getId();
                    xs << sConvertTime(time) << " [" << x->second->carType() << "] " << x->second->printing() << endl
                       << " is now a part of train [" << idx->getId()
                       << "] " << convertState(idx->getTrainState()) << " from " << idx->getFromStation() << " ("
                       << sConvertTime(idx->getDelayedDepTime()) << " to " << idx->getToStation() << " (" << sConvertTime(idx->getDelayedArrTime())
                       << ") delay (" << sConvertTime(idx->getDelayedTime()) << ")" << endl;
                    if(getLoglevel() == "High"){
                        ss << endl << " [" << x->second->carType() << "] ID: " << x->second->getId() << ", " << x->second->printing();
                    }
                    vehicleRoute.insert(make_pair(vehicleId, xs.str()));
                }

                cout << ss.str() << endl;
                writeToFile(ss.str());
                route.insert(make_pair(id, ss.str()));
            }
            break;
        }
    }

}
/**
 * Function that handles the running state and prints info to screen.
 * The print to screen differ depending on log level
 * For info, see printAssembled
 * @param id of the train
 * @param time simulation time
 * @return the arrival time
 */
int TrainControl::running(int id, int time){
    int arrTime = 0;
    double speed;
    speed = convertSpeed(id); // find the average speed the train needs to hold to get to the arrival station on time
    for(auto &idx : trains){
    if (idx && idx->getId() == id) {
        idx->setTrainState(RUNNING);
        if(idx->getDelayedArrTime() == idx->getArrTime()) {
            idx->setDelayedTime(0);
        }
        arrTime = idx->getDelayedArrTime(); // ArrTime is the same time as delayed arr time.
        if(time >= getStartTime()) {
            stringstream ss;
            ss << sConvertTime(time) << " Train [" << idx->getId() << "]";
            if(getLoglevel() == "Normal" || getLoglevel() == "High") {
                ss << " (" << convertState(idx->getTrainState()) << ") from "
                   << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << " (" << sConvertTime(idx->getDelayedDepTime()) << ") to "
                   << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(idx->getDelayedArrTime()) << ") delay ("
                   << sConvertTime(idx->getDelayedTime()) << ") speed = " << (int) speed << " km/h";
            }
            ss << " is now running";
            if(getLoglevel() == "Normal" || getLoglevel() == "High") {
                ss << ", arriving at the platform at "
                   << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(arrTime) << ")";
            }

            int vehicleId;
            auto it = trainPool.equal_range(idx->getId());
            for (auto x = it.first; x != it.second; ++x) {
                stringstream xs;
                vehicleId = x->second->getId();
                xs << sConvertTime(time) << " [" << x->second->carType() << "] " << x->second->printing() << endl
                   << " is now a part of train [" << idx->getId()
                   << "] " << convertState(idx->getTrainState()) << " from " << idx->getFromStation() << " ("
                   << sConvertTime(idx->getDelayedDepTime()) << " to " << idx->getToStation() << " (" << sConvertTime(idx->getDelayedArrTime())
                   << ") delay (" << sConvertTime(idx->getDelayedTime()) << ")" << endl;
                if(getLoglevel() == "High"){
                    ss << endl << " [" << x->second->carType() << "] ID: " << x->second->getId() << ", " << x->second->printing();
                }
                vehicleRoute.insert(make_pair(vehicleId, xs.str()));
            }

            cout << ss.str() << endl;
            writeToFile(ss.str());
            route.insert(make_pair(id, ss.str()));
        }
            break;
        }
    }
    return arrTime;
}

/**
 * Function that handles the arrived state and prints info to screen.
 * The print to screen differ depending on log level
 * For info, see printAssembled
 * @param id of the train
 * @param time simulation time
 */
void TrainControl::arrived(int id, int time){
    double speed;
    speed = convertSpeed(id);
    for(auto &idx : trains){
        if(idx && idx->getId() == id){
            idx->setTrainState(ARRIVED);
            if(time >= getStartTime()) {
                stringstream ss;
                ss << sConvertTime(time) << " Train [" << idx->getId() << "]";
                if(getLoglevel() == "Normal" || getLoglevel() == "High") {
                    ss << "(" << convertState(idx->getTrainState()) << ") from "
                       << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << " ("
                       << sConvertTime(idx->getDelayedDepTime())
                       << ") to " << idx->getToStation()
                       << " " << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(idx->getDelayedArrTime()) << ") delay ("
                       << sConvertTime(idx->getDelayedTime()) << ") " << (int) speed << " km/h";
                }
                ss << " has arrived at the platform";
                if(getLoglevel() == "Normal" || getLoglevel() == "High") {
                    ss << " at "
                       << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(idx->getDelayedArrTime()) << ")";
                }

                int vehicleId;
                auto it = trainPool.equal_range(idx->getId());
                for (auto x = it.first; x != it.second; ++x) {
                    stringstream xs;
                    vehicleId = x->second->getId();
                    xs << sConvertTime(time) << " [" << x->second->carType() << "] " << x->second->printing() << endl
                       << " is now a part of train [" << idx->getId()
                       << "] " << convertState(idx->getTrainState()) << " from " << idx->getFromStation() << " ("
                       << sConvertTime(idx->getDelayedDepTime()) << " to " << idx->getToStation() << " (" << sConvertTime(idx->getDelayedArrTime())
                       << ") delay (" << sConvertTime(idx->getDelayedTime()) << endl;
                    if(getLoglevel() == "High"){
                        ss << endl << " [" << x->second->carType() << "] ID: " << x->second->getId() << ", " << x->second->printing();
                    }
                    vehicleRoute.insert(make_pair(vehicleId, xs.str()));
                }

                cout << ss.str() << endl;
                writeToFile(ss.str());
                route.insert(make_pair(id, ss.str()));
            }
            break;
        }
    }
}

/**
 * Function that handles the finished state and prints info to screen.
 * The print to screen differ depending on log level
 * For info, see printAssembled
 * @param id of the train
 * @param time simulation time
 */
void TrainControl::finished(int id, int time){
    double speed;
    speed = convertSpeed(id);
    for(auto &idx : trains){
        if(idx && idx->getId() == id){
            idx->setTrainState(FINISHED);
            if(time >= getStartTime()) {
                stringstream ss;
                ss << sConvertTime(time) << " Train [" << idx->getId() << "]";
                if(getLoglevel() == "Normal" || getLoglevel() == "High") {
                    ss << " (" << convertState(idx->getTrainState()) << ") from "
                    << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << " (" << sConvertTime(idx->getDelayedDepTime()) << ") to "
                    << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(idx->getDelayedArrTime()) << ") delay (" << sConvertTime(idx->getDelayedTime())
                    << ") speed = " << (int) speed << "km/h";
                }
                ss << " is now disassembled.";

                int vehicleId = 0;
                auto it = trainPool.equal_range(idx->getId());
                for (auto x = it.first; x != it.second; ++x) {
                    stringstream xs;
                    vehicleId = x->second->getId();
                    xs << sConvertTime(time) << " [" << x->second->carType() << "] " << x->second->printing() << endl
                       << " is now a part of train [" << idx->getId()
                       << "] " << convertState(idx->getTrainState()) << " from " << idx->getFromStation() << " ("
                       << sConvertTime(idx->getDelayedDepTime()) << " to " << idx->getToStation() << " (" << sConvertTime(idx->getDelayedArrTime())
                       << ") delay (" << sConvertTime(idx->getDelayedTime()) << ")" << endl;
                    if(getLoglevel() == "High"){
                        ss << endl << " [" << x->second->carType() << "] ID: " << x->second->getId() << ", " << x->second->printing();
                    }
                    vehicleRoute.insert(make_pair(vehicleId, xs.str()));
                }
                cout << ss.str() << endl;
                writeToFile(ss.str());
                route.insert(make_pair(id, ss.str()));
            }
            unloadWagons(id, idx->getToStation()); // Unload the wagons at the arrival station
            simTime = time;
            break;
        }
    }
}

/**
 * Function that handles the incomplete state and prints info to screen.
 * The print to screen differ depending on log level
 * @param id of the train
 * @param time simulation time
 * @return the arrival time
 */
void TrainControl::incomplete(int id, int time) {
    for(auto &idx : trains){
        if(idx && idx->getId() == id){
            // If a train is incomplete, set the delayed departure time and delayed time and set delayed to true
            // Every time a train is incomplete, the time is added to the previous set time
            idx->setTrainState(INCOMPLETE);
            idx->setDelayedDepTime(time + DELAYED_DEPTIME);
            idx->setDelayedTime(idx->getDelayedTime() + DELAY);
            idx->setDelayed(true);
            if(time >= getStartTime()) {
                stringstream ss;
                ss << sConvertTime(time) << " Train [" << idx->getId() << "]";
                if(getLoglevel() == "Normal" || getLoglevel() == "High"){
                    ss << " (" << convertState(idx->getTrainState()) << ") from "
                       << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << " (" << sConvertTime(idx->getDelayedDepTime()) << ") to "
                       << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << " (" << sConvertTime(idx->getDelayedArrTime()) << ") delay ("
                       << sConvertTime(idx->getDelayedTime()) << ") speed = 0 km/h";
                }
                ss << " is now incomplete";
                if(getLoglevel() == "Normal" || getLoglevel() == "High") {
                    ss << ", next try at "
                       << sConvertTime(time + DELAY);
                }

                int vehicleId;
                auto it = trainPool.equal_range(idx->getId());
                for (auto x = it.first; x != it.second; ++x) {
                    stringstream xs;
                    vehicleId = x->second->getId();
                    xs << sConvertTime(time) << " [" << x->second->carType() << "] " << x->second->printing() << endl
                       << " is now a part of train [" << idx->getId()
                       << "] " << convertState(idx->getTrainState()) << " from " << idx->getFromStation() << " ("
                       << sConvertTime(idx->getDelayedDepTime()) << " to " << idx->getToStation() << " (" << sConvertTime(idx->getDelayedArrTime())
                       << ") delay (" << sConvertTime(idx->getDelayedTime()) << ")" << endl;
                    if(getLoglevel() == "High"){
                        ss << endl << " [" << x->second->carType() << "] ID: " << x->second->getId() << ", " << x->second->printing();
                    }
                    vehicleRoute.insert(make_pair(vehicleId, xs.str()));
                }

                cout << ss.str() << endl;
                writeToFile(ss.str());
                route.insert(make_pair(id, ss.str()));
            }
            break;
        }
    }
}

/**
 * Function that convert the enum values (0-6) into strings
 * @param state the state of the train (0-6)
 * @return state string
 */
string TrainControl::convertState(trainState state){
    switch(state){
        case 0:
            return "NOT ASSEMBLED";
            break;
        case 1:
            return "ASSEMBLED";
            break;
        case 2:
            return "READY";
            break;
        case 3:
            return "RUNNING";
            break;
        case 4:
            return "ARRIVED";
            break;
        case 5:
            return "FINISHED";
            break;
        case 6:
            return "INCOMPLETE";
            break;
        default:
            return "error";
    }
}

///////////////////////////////////////////////////////////////////
// Train Menu Functions
///////////////////////////////////////////////////////////////////
/**
 * Function that prints info about one train
 * @param num Train number
 */
void TrainControl::showTrainByNumber(int num){
    for(auto &i : trains){
        if(i && i->getId() == num){
            // If a train is not assembled yet, print a string that informs the user about this
            if(i->getTrainState() == NOT_ASSEMBLED){
                cout << "Train [" << i->getId() << "] (" << convertState(i->getTrainState()) << ") from "
                     << i->getFromStation() << " " << sConvertTime(i->getDepTime()) << " to " << i->getToStation()
                     << " " << sConvertTime(i->getArrTime()) << " has not been assembled yet." << endl;
                i->wagonPrint(i->getWagons());
                cout << endl << endl;
            }
            // Else, print the info about all states the train has been through
            else{
                for(auto &idx : route){
                    if(idx.first == num){
                        cout << idx.second << endl << endl;
                    }
                }
            }
        }
    }
}

/**
 * Function that prints info about a train, found by searching for a vehicle that is/has been attached to the train
 * @param id of an vehicle
 */
void TrainControl::showTrainByVehicle(int id){
    auto it = vehicleRoute.equal_range(id);

    for (auto itr = it.first; itr != it.second; ++itr) {
        cout << itr->second << endl << endl;
    }
}

/**
 * Function that prints the train scheduale for all stations
 */
void TrainControl::showTrainSchedule(){
    for(const auto &idx : trains){
        cout << idx->getFromStation() << ": " << sConvertTime(idx->getDepTime()) << " Train [" << idx->getId() << "] to "
        << idx->getToStation() << " arriving " << sConvertTime(idx->getArrTime()) << endl;
    }
}

/**
 * Function that prints info about all trains
 */
void TrainControl::showAllTrains(){
    int speed = 0;
    for(auto &idx : trains){
            if(idx->getTrainState() < 1){ idx->getMaxSpeed(); }
            cout << " Train [" << idx->getId() << "] (" << convertState(idx->getTrainState()) << ") from "
                 << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << " to " << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << " delay "
                 << " speed = " << speed << "km/h" << endl;
            idx->wagonPrint(idx->getWagons());
    }
}

///////////////////////////////////////////////////////////////////
// Station Menu Functions
///////////////////////////////////////////////////////////////////
/**
 * Function that prints all the names of available stations
 */
void TrainControl::showStationNames(){
    for( auto idx = vehiclePool.begin(), end = vehiclePool.end();
        idx != end;
        idx = vehiclePool.upper_bound(idx->first)){
        cout << idx->first << endl;
    }
}

/**
 * Function that prints all trains and vehicles at one station
 * @param stationName the name of the station that the user wants info about
 */
void TrainControl::showStationByName(std::string stationName){

    auto p = vehiclePool.equal_range(stationName);
    cout << "Available vehicles at the station:" << endl << endl;
    for (auto it = p.first; it != p.second; ++it) {
        cout << "[" << it->second->carType() << "] id: " << it->second->getId();
        if(getLoglevel() == "Normal" || getLoglevel() == "High"){
           cout << ", " << it->second->printing();
        }
        cout << endl;
    }

    cout << endl << "Avaiable trains at the station:" << endl << endl;
    int speed = 0;
    for(auto &idx: trains){
        if(idx->getFromStation() == stationName || idx->getToStation() == stationName){
            if(idx->getTrainState() == ASSEMBLED || idx->getTrainState() == READY || idx->getTrainState() == ARRIVED){
                cout << "Train [" << idx->getId() << "]";
                if(getLoglevel() == "Normal" || getLoglevel() == "High"){
                    cout << " (" << convertState(idx->getTrainState()) << ") from "
                         << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << "(" << sConvertTime(idx->getDelayedDepTime()) << ") to "
                         << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << "(" << sConvertTime(idx->getDelayedArrTime()) << ") delay ("
                         << sConvertTime(idx->getDelayedTime()) << ") speed = " << speed << "km/h";
                }
                cout << endl;
                if(getLoglevel() == "High"){
                    for(auto &i : trainPool){
                        if(i.first == idx->getId()){
                            cout << "\t[" << i.second->carType() << "] ID: " << i.second->getId();
                            cout << ", " << i.second->printing();
                            cout << endl;
                        }
                    }
                }
               cout << endl;
            }
        }
    }
}

/**
 * Function that prints info of all vehicles and trains at all stations
 */
void TrainControl::showAllStations(){
    cout << "Wagons available at all stations: " << endl << endl;
    for(const auto &idx : vehiclePool){
        cout << idx.first << " [" << idx.second->carType() << "]";
        if(getLoglevel() == "Normal" || getLoglevel() == "High"){
            cout << ", " << idx.second->printing();
        }
        cout  << endl;
    }

    cout << endl << "Trains available at all stations: " << endl << endl;
    int speed = 0;
    for(auto &idx: trains){
            if(idx->getTrainState() == ASSEMBLED || idx->getTrainState() == READY || idx->getTrainState() == ARRIVED){
                cout << "Train [" << idx->getId() << "]";
                if(getLoglevel() == "Normal" || getLoglevel() == "High"){
                    cout << " (" << convertState(idx->getTrainState()) << ") from "
                         << idx->getFromStation() << " " << sConvertTime(idx->getDepTime()) << "(" << sConvertTime(idx->getDelayedDepTime()) << ") to "
                         << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << "(" << sConvertTime(idx->getDelayedArrTime()) << ") delay ("
                         << sConvertTime(idx->getDelayedTime()) << ") speed = " << speed << "km/h";
                }
                cout << endl;
                if(getLoglevel() == "High"){
                    for(auto &i : trainPool){
                        if(i.first == idx->getId()){
                            cout << "\t[" << i.second->carType() << "] ID: " << i.second->getId();
                            cout << ", " << i.second->printing();
                            cout << endl;
                        }
                    }
                }
            }
            cout << endl;
    }
}

///////////////////////////////////////////////////////////////////
// Vehicle Menu Functions
///////////////////////////////////////////////////////////////////

/**
 * Show the information of one vehicle, choosen by id
 * @param id vehicle id
 */
void TrainControl::showVehicleById(int id){
    for(auto &idx : vehiclePool){
        if(idx.second->getId() == id){
            cout << "[" << idx.second->carType() << "] " << idx.second->printing();
            // If log level is higher than low, print more information about the vehcile
            if(getLoglevel() == "Normal" || getLoglevel() == "High"){
                cout << " is at " << idx.first << " waiting to be assembled.";
            }
            cout << endl;
            break;
        }
    }
    // If train is assembled
    for(auto &idx : trainPool){
        if(idx.second->getId() == id){
            cout << "[" << idx.second->carType() << "] " << idx.second->printing() << endl;
            if(getLoglevel() == "Normal" || getLoglevel() == "High"){
                for(auto &i : trains){
                    if(idx.first == i->getId())
                    {
                        cout << "is attached to train " << i->getId();
                    }
                }
            }
            if(getLoglevel() == "High"){
                for(auto &i : trains){
                    if(idx.first == i->getId())
                    {
                        cout << ", which for the moment is " << convertState(i->getTrainState());
                        if(i->getTrainState() == ASSEMBLED || i->getTrainState() == READY || i->getTrainState() == RUNNING)
                        {
                            cout << ", arriving at " << i->getToStation() << " at "<< sConvertTime(i->getDelayedArrTime()) << endl;
                        }
                        else if(i->getTrainState() == ARRIVED){
                            cout << " and arrived at the platform at " << i->getToStation() << " at " << sConvertTime(i->getDelayedArrTime()) << endl;
                        }
                    }
                }
            }
            cout << endl;
            break;
        }
    }
}

/**
 * Show the information of all vehicles
 */
void TrainControl::showAllVehicles(){
    // If a vehicle is not a part of a train
    for(auto &idx : vehiclePool){
        cout << "[" << idx.second->carType() << "] id: " << idx.second->getId() << ", " << idx.second->printing();
        if(getLoglevel() == "Normal" || getLoglevel() == "High") {
            cout << endl << "is at " << idx.first << " waiting to be assembled.";
        }
        if(getLoglevel() == "High"){

        }
        cout << endl;
    }
    // If a vehicle is attached to a train
    for(auto &idx : trainPool){
        cout << "[" << idx.second->carType() << "] id: " << idx.second->getId() << ", " << idx.second->printing() << endl;
        if(getLoglevel() == "Normal" || getLoglevel() == "High"){
            for(auto &i : trains){
                if(idx.first == i->getId())
                {
                    cout << "is attached to train [" << i->getId() << "]";
                }
            }
        }
        if(getLoglevel() == "High"){
            for(auto &i : trains){
                if(idx.first == i->getId())
                {
                    cout << ", which for the moment is " << convertState(i->getTrainState());
                    if(i->getTrainState() == ASSEMBLED || i->getTrainState() == READY || i->getTrainState() == RUNNING)
                    {
                        cout << ", arriving at " << i->getToStation() << " at "<< sConvertTime(i->getDelayedArrTime()) << endl;
                    }
                    else if(i->getTrainState() == ARRIVED){
                        cout << " and arrived at the platform at " << i->getToStation() << " at " << sConvertTime(i->getDelayedArrTime()) << endl;
                    }
                }
            }
        }
        cout << endl;
    }
}


///////////////////////////////////////////////////////////////////
// Statistics Menu Functions
///////////////////////////////////////////////////////////////////
/**
 * Function that prints the statistic of the simulation, when simulation is done.
 */
void TrainControl::printStatistics(){
    cout << "Number of vehicles at start of simulation:" << endl;
    for(auto &idx : trainStationValues){
        cout << idx << endl;
    }

    // Print all the trains that has reached their end station and was not delayed.
    cout << endl << endl << "Trains that was not delayed: " << endl << endl;
    for(auto &idx : trains){
        // If train has status finished, was not delayed and was printed during the simulation time
        if(idx->getTrainState() == FINISHED && idx->getDelayed() == 0 && route.count(idx->getId()) > 0){
            cout << "Train: [" << idx->getId() << "] from " << idx->getFromStation() << " to " << idx->getToStation() << endl;
            idx->wagonPrint(idx->getWagons());
        }
        cout << endl;
    }

    // Total delay time, time for end of simulation and the trains that never left the station
    cout << endl << endl << "Total delay time = ";
    int hour, minutes, depHour, depTime = 0, arrTime = 0;
    hour = delayedTime/60;
    minutes = delayedTime%60;
    cout << hour << "h " << minutes << "min" << endl;

    for(auto &i : trains){
        if(i && i->getDelayed() && i->getTrainState() != INCOMPLETE) {
            depTime += (i->getDelayedDepTime() - i->getDepTime());
            arrTime += (i->getDelayedArrTime() - i->getArrTime());
        }
    }
    cout << "Total delay at departure stations = ";
    hour = depTime/60;
    minutes = depTime%60;
    cout << hour << "h " << minutes << "min" << endl;
    cout << "Total delay at arrival stations = ";
    hour = arrTime/60;
    minutes = arrTime%60;
    cout << hour << "h " << minutes << "min" << endl << endl;
    cout << "End time for simulation = " << sConvertTime(simTime) << endl << endl;
    cout << "Trains that never left the station:" << endl << endl;
    for(auto &idx : trains){
        // create a tmp vector from wagons, to keep track of the missing vehicles
        vector<string>tmp;
        string type, wagons = idx->getWagons();
        size_t p = wagons.find_first_not_of(' '); // Make sure the string does not start with a white space
        wagons.erase(0, p);
        stringstream line(wagons);

        // Push back all the values to a vector.
        while(getline(line, type, ' ')){
            tmp.push_back(convertType(type));
        }
        if(idx && idx->getTrainState() == INCOMPLETE){
            cout << "Train [" << idx->getId() << "] from " << idx->getFromStation() << " "
                 << sConvertTime(idx->getDepTime()) << " to " << idx->getToStation() << " " << sConvertTime(idx->getArrTime()) << endl;
            cout << setw(4) << "Vehicles:" << endl;
            for(auto &i : trainPool){
                if(i.first == idx->getId()){
                    cout << setw(8) << "[" << i.second->carType() << "] " << i.second->getId() << ", " << i.second->printing();
                    cout << endl;
                    // Erase the found vehicle from the tmp vector, to only print the missing vehicles from the vector.
                    auto found = std::find(tmp.begin(), tmp.end(), i.second->carType()) ;
                    if (found!=tmp.end())
                        tmp.erase(found);
                }
            }
            cout << setw(4) << "Missing vehicles:" << endl;

            for(auto &t : tmp){
                cout << setw(8) << t << endl;
            }

            cout << endl;
        }
    }

    // Delayed trains, that is not incomplete
    cout << "Delayed trains:" << endl << endl;
    for(auto &i : trains){
        if(i && i->getDelayed() && i->getTrainState() != INCOMPLETE){
            cout << "Train [" << i->getId() << "] from " << i->getFromStation() << " " << sConvertTime(i->getDepTime())
                 << " (" << sConvertTime(i->getDelayedDepTime()) << ") to " << i->getToStation() << " " << sConvertTime(i->getArrTime())
                 << " (" << sConvertTime(i->getDelayedArrTime()) << ")" << endl;
        }
    }
}