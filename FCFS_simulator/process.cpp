#include "process.h"

process::process(int burst, int time, int id)
{
    pid = id;
    burstTime = burst;
    burstTimeLeft = burst;
    arrivalTime = time;
    seenFlag = false;
    initialWaitTime = 0;
    totalWaitTime = 0;
}

void process::setPid(int num)
{
    pid = num;
}

bool process::hasBeenSeen()
{
    return seenFlag;
}

int process::getBurstTime()
{
    return burstTime;
}

int process::getPid()
{
    return pid;
}

void process::setArrivalTime(int time)
{
    arrivalTime = time;
}

int process::getArrivalTime()
{
    return arrivalTime;
}

int process::getBurstTimeLeft()
{
    return burstTimeLeft;
}

void process::decreaseBurstTime()
{
    burstTimeLeft -=1;
}

int process::getInitialWaitTime()
{
    return initialWaitTime;
}

int process::getTotalWaitTime()
{
    return totalWaitTime;
}

void process::addWaitTime(int time)
{
    totalWaitTime += time;
}

void process::setSeenFlag(int time)
{
    seenFlag = true;
    initialWaitTime = time;
    totalWaitTime = time;
}
