//------------------------------------------------------------------------------
// main.cpp DT060G Objektorienterad programmering i C++
// Author: Emelie Fogelström emfo1201@student.miun.se
// Version: 1.0
// Date: 2019-05-23
//------------------------------------------------------------------------------

#ifndef OO_PROJEKT2019_CONSTANTS_H
#define OO_PROJEKT2019_CONSTANTS_H


enum trainState {
    NOT_ASSEMBLED = 0,
    ASSEMBLED,
    READY,
    RUNNING,
    ARRIVED,
    FINISHED,
    INCOMPLETE
};

const int DELAY = 10;
const int DELAYED_DEPTIME = 40;
const int SCHEDULE_BUILD = 30;
const int SCHEDULE_READY = 20;
const int SCHEDULE_LEAVE = 10;
const int SCHEDULE_FINISHED = 20;

#endif //OO_PROJEKT2019_CONSTANTS_H
