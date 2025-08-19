#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

using namespace std;

class Scheduler
{
private:
    vector <Process> incomingProcesses;

    int contextSwitchDelay = 14;
    double totalTurnaroundTime = 0.0;
    double totalWaitTime = 0.0;
    double totalInitialTime = 0.0;
    double maxTurnaroundTime = 0.0;
    double minTurnaroundTime = 5000.0;
    double maxWaitTime;
    double minWaitTime;
    double maxInitialTime;
    double minInitialTime;

    vector<Process> extractReadyProcesses(int systemTime);
    void updateInitialWaitStatistics(vector<Process>& queue, int systemTime);
    void updateCompletionStatistics(vector<Process>& queue, int systemTime);
    void createProcessesWithZeroArrival(int num_zero);
    void createProcessesWithRandomArrival(int num_rand, int num_zero);


public:
    Scheduler(double minWait, double maxWait, double minInitial, double maxInitial);
    void createProcesses(int numberOfProcesses);
    void simulateFCFS();
    void printStatistics(int numberOfProcesses);
};

#endif // SCHEDULER_H
