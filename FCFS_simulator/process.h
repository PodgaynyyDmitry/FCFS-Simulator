#ifndef PROCESS_H
#define PROCESS_H

class Process
{
private:
    int arrivalTime;
    int burstTime;
    int burstTimeLeft;
    bool started;
    int initialWaitTime;
    int pid;
public:
    Process(int burst, int time, int id);
    void setArrivalTime(int time);
    int getArrivalTime();
    int getBurstTime();
    int getBurstTimeLeft();
    void decreaseBurstTime();
    int getInitialWaitTime();
    bool hasStarted();
    void markStarted();
    void setInitialTime(int time);
    int getPid();
};

#endif // PROCESS_H
