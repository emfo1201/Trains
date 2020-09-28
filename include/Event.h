//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-27
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_EVENT_H
#define OO_PROJEKT2019_EVENT_H

// Forward declarations
class Simulation;
class TrainControl;

class Event {
public:
    // Constructor requires time of event
    explicit Event (unsigned int t) : time(t) { }

    virtual ~Event() = default;

    // Process event by invoking this method
    virtual void processEvent()=0;

    // Get time for this event
    unsigned int getTime() const {
        return time;
    }

protected:
    // Time for this event
    unsigned int time;
};



// Used to compare to Events with respect to time
class EventComparison {
public:
    bool operator() (Event * left, Event * right) {
        return left->getTime() > right->getTime();
    }
};

//--- Derived Event-classes ----------------------------------------------------


class AssembledEvent : public Event {
public:
    AssembledEvent (Simulation *sim, TrainControl *theTC, int time, int iId)
            : Event((unsigned int) time),theSim(sim),trainControl(theTC),id(iId) { }

    void processEvent() override;

protected:
    Simulation *theSim;
    TrainControl *trainControl;
    int id;
};



class ReadyEvent : public Event {
public:
    ReadyEvent(Simulation *sim, TrainControl *theTC, int time, int iId )
            :Event((unsigned int) time),theSim(sim),trainControl(theTC),id(iId) { }

    void processEvent() override;

protected:
    Simulation *theSim;
    TrainControl *trainControl;
    int id;
};



class IncompleteEvent : public Event {
public:
    IncompleteEvent(Simulation *sim, TrainControl *theTC, int time, int iId )
            :Event((unsigned int) time),theSim(sim),trainControl(theTC),id(iId) { }

    void processEvent() override;

protected:
    Simulation *theSim;
    TrainControl *trainControl;
    int id;
};


class RunningEvent : public Event {
public:
    RunningEvent (Simulation *sim, TrainControl *theTC, int time, int iId)
            :Event((unsigned int) time),theSim(sim),trainControl(theTC),id(iId) { }

    void processEvent() override;

protected:
    Simulation *theSim;
    TrainControl *trainControl;
    int id;
};


class ArrivedEvent : public Event {
public:
    ArrivedEvent (Simulation *sim, TrainControl *theTC, int time, int iId)
            : Event((unsigned int) time),theSim(sim),trainControl(theTC), id(iId) { }

    void processEvent() override;

protected:
    Simulation *theSim;
    TrainControl *trainControl;
    int id;
};

class FinishedEvent : public Event {
public:
    FinishedEvent (Simulation *sim, TrainControl *theTC, int time, int iId)
            : Event((unsigned int) time),theSim(sim),trainControl(theTC),id(iId) { }

    void processEvent() override;

protected:
    Simulation *theSim;
    TrainControl *trainControl;
    int id;
};
#endif //OO_PROJEKT2019_EVENT_H
