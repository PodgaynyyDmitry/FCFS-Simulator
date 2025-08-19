#include "scheduler.h"
#include <time.h>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;
scheduler::scheduler(double minWait, double maxWait, double minInitial, double maxInitial)
{
    maxWaitTime = maxWait;
    minWaitTime = minWait;
    maxInitialTime = maxInitial;
    minInitialTime = minInitial;
}

void scheduler::createProcessesWithZeroArrival(int numZeroTimeProcesses)
{
    int randomBurstTime;
    for (int i = 0; i < numZeroTimeProcesses; i++)
    {
        randomBurstTime= (rand()%3500)+500;
        process temp(randomBurstTime, 0, i+1);
        incomingProcesses.push_back(temp);
    }
}

void scheduler::createProcessesWithRandomArrival(int numNonZeroTimeProcesses, int numZeroTimeProcesses)
{
    int randomBurstTime;
    for(int i = 0; i < numNonZeroTimeProcesses; i++)
    {
        randomBurstTime= (rand()%3500)+500;
        double lambda = 0.001;
        double r = ((double) rand()/(RAND_MAX));
        double x = -(log(r)/lambda);
        if ( x > 8000 ) { i--; continue; }
        process temp(randomBurstTime, (int)x, (numZeroTimeProcesses + i+1));
        incomingProcesses.push_back(temp);
    }
}

void scheduler::createProcesses(int numberOfProcesses)
{
    srand((unsigned)time(0));
    int numNonZeroTimeProcesses = numberOfProcesses * .8;
    int numZeroTimeProcesses = numberOfProcesses - numNonZeroTimeProcesses;
    createProcessesWithZeroArrival(numZeroTimeProcesses);
    createProcessesWithRandomArrival(numNonZeroTimeProcesses, numZeroTimeProcesses);
}

vector<process> scheduler::extractReadyProcesses(int systemTime)
{
    int numberOfProcesses = incomingProcesses.size();
    vector <process> queue;

    for(unsigned int i = 0; i < numberOfProcesses; i++)
    {
        if (incomingProcesses[i].getArrivalTime() <= systemTime)
        {
            queue.push_back(incomingProcesses[i]);
            cout << "[time " << incomingProcesses[i].getArrivalTime() << "ms] Process "
                 << incomingProcesses[i].getPid() << " created (requires "
                 << incomingProcesses[i].getBurstTime() << "ms CPU time)" << endl;
            incomingProcesses.erase(incomingProcesses.begin() + i);
            numberOfProcesses--;
            i--;
        }
    }
    return queue;
}

void scheduler::updateInitialWaitStatistics(vector<process>& queue, int systemTime)
{
    int arrivalTime = systemTime - queue[0].getArrivalTime();
    queue[0].markStarted();
    queue[0].setArrivalTime(arrivalTime);
    totalInitialTime += arrivalTime;
    if (arrivalTime < minInitialTime)
        minInitialTime = arrivalTime;
    if (arrivalTime > maxInitialTime)
        maxInitialTime = arrivalTime;
    cout << "[time " << systemTime << "ms] Process "
         << queue[0].getPid() << " accessed CPU for the first time (initial wait time "
         << queue[0].getInitialWaitTime() << "ms)" << endl;
}

void scheduler::updateCompletionStatistics(vector<process>& queue, int systemTime)
{
    int waitTime = ((systemTime + 1) - queue[0].getBurstTime() - queue[0].getArrivalTime());
    cout << "[time " << systemTime + 1
         << "ms] Process " << queue[0].getPid()
         << " completed its CPU burst (turnaround time "
         << ((systemTime + 1) - queue[0].getArrivalTime())
         << "ms, initial wait time " << queue[0].getInitialWaitTime()
         << "ms, total wait time " << waitTime << "ms)" << endl;

    int turnTime = ((systemTime + 1) - queue[0].getArrivalTime());
    totalTurnaroundTime += turnTime;
    totalWaitTime += waitTime;
    if (waitTime < minWaitTime)
        minWaitTime = waitTime;
    if (waitTime > maxWaitTime)
        maxWaitTime = waitTime;
    if (turnTime < minTurnaroundTime)
        minTurnaroundTime = turnTime;
    if (turnTime > maxTurnaroundTime)
        maxTurnaroundTime = turnTime;
}

void scheduler::simulateFCFS()
{
    int numberOfCompletedProcesses = 0;
    int systemTime = 0;
    int lastPid = 0;
    vector <process> queue;
    int numberOfProcesses =incomingProcesses.size();

    while(numberOfCompletedProcesses != numberOfProcesses)
    {
        vector <process> arrivals = extractReadyProcesses(systemTime);
        queue.insert(queue.end(), arrivals.begin(), arrivals.end());

        if (queue.size() != 0)
        {
            if (queue[0].hasStarted() == false)
                updateInitialWaitStatistics(queue, systemTime);

            queue[0].decreaseBurstTime();

            if (queue[0].getBurstTimeLeft() == 0)
            {
                updateCompletionStatistics(queue, systemTime);
                lastPid = queue[0].getPid();
                queue.erase(queue.begin());
                numberOfCompletedProcesses++;

                if (queue.size() != 0)
                {
                    cout << "[time " << systemTime + 1 << "ms] Context switch (swapped out process "
                         << lastPid << " for process " << queue[0].getPid() << ")" << endl;

                    systemTime = systemTime + contextSwitchDelay;
                }
            }
        }
        systemTime++;
    }
}

void scheduler::printStatistics(int numberOfProcesses)
{
    cout << fixed << setprecision(3);
    cout << endl;
    cout << "Turnaround time: min " << minTurnaroundTime
         << "ms; avg " << totalTurnaroundTime / numberOfProcesses
         << "ms; max " << maxTurnaroundTime << "ms" << endl;

    cout << "Initial wait time: min " << minInitialTime
         << "ms; avg " << totalInitialTime / numberOfProcesses
         << "ms; max " << maxInitialTime << "ms" << endl;

    cout << "Total wait time: min " << minWaitTime
         << "ms; avg " << totalWaitTime / numberOfProcesses
         << "ms; max " << maxWaitTime << "ms" << endl << endl;
}

