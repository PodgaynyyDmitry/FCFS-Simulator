#include "process.h"

Process::Process(int burst, int time, int id)
{
    pid = id;
    burstTime = burst;
    burstTimeLeft = burst;
    arrivalTime = time;
    started = false;
    initialWaitTime = 0;
}

bool Process::hasStarted()
{
    return started;
}

int Process::getBurstTime()
{
    return burstTime;
}

int Process::getPid()
{
    return pid;
}

void Process::setArrivalTime(int time)
{
    arrivalTime = time;
}

int Process::getArrivalTime()
{
    return arrivalTime;
}

int Process::getBurstTimeLeft()
{
    return burstTimeLeft;
}

void Process::decreaseBurstTime()
{
    burstTimeLeft -=1;
}

int Process::getInitialWaitTime()
{
    return initialWaitTime;
}

void Process::markStarted()
{
    started = true;

}
void Process::setInitialTime(int time)
{
     initialWaitTime = time;
}
