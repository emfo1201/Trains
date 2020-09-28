//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-30
//------------------------------------------------------------------------------

#include "../include/Simulation.h"
#include "../include/Event.h"
#include <iostream>

// Execute events until event queue is empty
bool Simulation::run()
{
    if(eventQueue.empty()){
        return false;
    }
    Event * nextEvent = eventQueue.top();
    eventQueue.pop();
    nextEvent->processEvent();
    if(eventQueue.empty())
         return false;
    delete nextEvent;
    nextEvent = nullptr;

    return true;
}

// Push back all events to the queue
void Simulation::scheduleEvent (Event * newEvent) {
    eventQueue.push (newEvent);
}

// Run the next event in queue
bool Simulation::runNextEvent(){
    currentTime = eventQueue.top()->getTime();
    return run();
}


// Run interval from current time to current time + interval time
bool Simulation::runInterval(int time) {
    currentTime += time;
    while(eventQueue.top()->getTime() <= currentTime)
    {
         if(eventQueue.empty()){
            return false;
        }
        Event * nextEvent = eventQueue.top();
        eventQueue.pop();
        nextEvent->processEvent();
        if(eventQueue.empty())
            return false;
        delete nextEvent;
        nextEvent = nullptr;
    }
    return true;
}

// Run the whole simulation
void Simulation::runAll() {
   while(!eventQueue.empty()){
       run();
   }
}