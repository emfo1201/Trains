//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-27
//------------------------------------------------------------------------------

#include "../include/Event.h"
#include "../include/TrainControl.h"
#include "../include/Simulation.h"

/**
 * Function that tries to assemble train and if possible, schedule next event (ReadyEvent).
 * If not possible, set as incomplete and try again in 10 minutes.
 */
void AssembledEvent::processEvent()
{
    if(time < trainControl->getEndTime()) {
        if (trainControl->assembleTrain(id)) {
            trainControl->printAssembled(id, getTime());
            time += SCHEDULE_READY;
            theSim->scheduleEvent(new ReadyEvent(theSim, trainControl, time, id));
        }
        else{
            trainControl->incomplete(id, time);
            time += DELAY;
            theSim->scheduleEvent(new IncompleteEvent(theSim, trainControl, time, id));
        }
    }
}


/**
 * Function that schedule next event (RunningEvent)
 */
void ReadyEvent::processEvent()
{
    if(trainControl->getEndTime() == 1439 || time < trainControl->getEndTime()) {
        trainControl->ready(id, getTime());
        time += SCHEDULE_LEAVE;
        theSim->scheduleEvent(new RunningEvent(theSim, trainControl, time, id));
    }
}

/**
 * Function that tries to assemble train again and if possible, schedules next event (ReadyEvent)
 * and if not possible, schedules next try to assemble train
 */
void IncompleteEvent::processEvent(){
    if(time < trainControl->getEndTime()) {
        if (trainControl->tryAssembleAgain(id)) {
            trainControl->printAssembled(id, getTime());
            time += SCHEDULE_READY;
            theSim->scheduleEvent(new ReadyEvent(theSim, trainControl, time, id));
        }
        else{
            trainControl->incomplete(id, getTime());
            time += DELAY;
            theSim->scheduleEvent(new IncompleteEvent(theSim, trainControl, time, id));
        }
    }
}

/**
 * Function that schedule next event (ArrivedEvent)
 */
void RunningEvent::processEvent() {
    if(trainControl->getEndTime() == 1439 || time < trainControl->getEndTime()) {
        int arrTime = trainControl->running(id, getTime());
        time = (unsigned int) arrTime;
        theSim->scheduleEvent(new ArrivedEvent(theSim, trainControl, time, id));
    }
}

/**
 * Function that schedule next event (FinishedEvent)
 */
void ArrivedEvent::processEvent() {
    if(trainControl->getEndTime() == 1439 || time < trainControl->getEndTime()) {
        trainControl->arrived(id, getTime());
        time += SCHEDULE_FINISHED;
        theSim->scheduleEvent(new FinishedEvent(theSim, trainControl, time, id));
    }
}

/**
 * Funciton that is called when event is over, and train is ready to be disassembled.
 */
void FinishedEvent::processEvent() {
    if(trainControl->getEndTime() == 1439 || time < trainControl->getEndTime()) {
        trainControl->finished(id, getTime());
    }
}