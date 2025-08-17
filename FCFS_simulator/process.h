#ifndef PROCESS_H
#define PROCESS_H

class process
{
private:
    int arrivalTime; //время начала
    int burstTime; // Требуемоу время для выполнения процесса
    int burstTimeLeft; // Оставшееся время выполнения процесса
    bool seenFlag;
    int initialWaitTime;
    int totalWaitTime;
    int pid;
public:
    process(int burst, int time, int id, int importance);
    void setArrivalTime(int time);
    void setPid(int num);
    int getArrivalTime();
    int getBurstTime();
    int getBurstTimeLeft();
    void decreaseBurstTime();
    int getInitialWaitTime();
    int getTotalWaitTime();
    void addWaitTime(int time);
    bool hasBeenSeen();
    void setSeenFlag(int time);
    int getPid();
};

#endif // PROCESS_H
