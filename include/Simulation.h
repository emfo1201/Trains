//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-30
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_SIMULATOR_H
#define OO_PROJEKT2019_SIMULATOR_H
#include <queue>
#include <vector>
#include "Event.h"

using std::priority_queue;
using std::vector;

class Simulation {
public:
    Simulation () : currentTime(0), eventQueue() { }
    ~Simulation()= default;
    // Add a new event to event queue.
    void scheduleEvent (Event * newEvent);

    void setTime(int time) { currentTime = time; }
    int getTime() const { return currentTime; }
    bool runNextEvent();
    bool runInterval(int time);
    void runAll();
    bool run();

private:
    int currentTime; // Time for last processed event

    /* The event queue. Always sorted with respect to the times
       for the events. The event with the 'smallest' time is always
       placed first in queue and will be processed next. */

    priority_queue<Event*, vector<Event*>, EventComparison> eventQueue;
};
#endif //OO_PROJEKT2019_SIMULATOR_H
