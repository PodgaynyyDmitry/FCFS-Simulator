#ifndef PROCESS_H
#define PROCESS_H

class process
{
private:
    int arrivalTime;
    int burstTime;
    int burstTimeLeft;
    bool seenFlag;
    int initialWaitTime;
    int pid;
public:
    process(int burst, int time, int id);
    void setArrivalTime(int time);
    int getArrivalTime();
    int getBurstTime();
    int getBurstTimeLeft();
    void decreaseBurstTime();
    int getInitialWaitTime();
    int getTotalWaitTime();
    bool hasBeenSeen();
    void setSeenFlag(int time);
    int getPid();
};

#endif // PROCESS_H
