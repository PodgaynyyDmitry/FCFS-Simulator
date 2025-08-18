#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

using namespace std;

class scheduler
{
private:
    vector <process> processes;

    int contextSwitch = 14;
    double totalTurnaround = 0.0;
    double totalWaitTime = 0.0;
    double totalInitialTime = 0.0;
    double maxTurnaround = 0.0;
    double minTurnaround = 5000.0;
    double maxWaitTime;
    double minWaitTime;
    double maxInitialTime;
    double minInitialTime;

    vector<process> getQueueForExequte(vector<process>& processes, int clock);
    void changeInitialStatistics(vector<process>& queue, int clock);
    void changeCompletedStatistics(vector<process>& queue, int clock);
    void createZeroArrivalTimeProcesses(vector<process>& processe, int num_zero);
    void createProcesses(vector<process>& processe, int num_rand, int num_zero);


public:
    scheduler();
    void createProcesses(int numberOfProcesses);
    void firstComeFirstServe();

    void setMinWaitTime(double time);
    void setMaxWaitTime(double time);
    void setMinInitialTime(double time);
    void setMaxInitialTime(double time);

    void statistics(int numberOfProcesses);
};

#endif // SCHEDULER_H
