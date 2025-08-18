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

void scheduler::createZeroArrivalTimeProcesses(int numZeroTimeProcesses)
{
    int randomBurstTime;
    for (int i = 0; i < numZeroTimeProcesses; i++)
    {
        randomBurstTime= (rand()%3500)+500;
        process temp(randomBurstTime, 0, i+1);
        processes.push_back(temp);
    }
}

void scheduler::createProcesses(int numNonZeroTimeProcesses, int numZeroTimeProcesses)
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
        processes.push_back(temp);
    }
}

void scheduler::createProcesses(int numberOfProcesses)
{
    srand((unsigned)time(0));
    int numNonZeroTimeProcesses = numberOfProcesses * .8;
    int numZeroTimeProcesses = numberOfProcesses - numNonZeroTimeProcesses;
    createZeroArrivalTimeProcesses(numZeroTimeProcesses);
    createProcesses(numNonZeroTimeProcesses, numZeroTimeProcesses);
}

vector<process> scheduler::getQueueForExequte(vector<process>& processes, int systemTime)
{
    int numberOfProcesses = processes.size();
    vector <process> queue;

    for(unsigned int i = 0; i < numberOfProcesses; i++)
    {
        if (processes[i].getArrivalTime() <= systemTime)
        {
            queue.push_back(processes[i]);
            cout << "[time " << processes[i].getArrivalTime() << "ms] Process "
                 << processes[i].getPid() << " created (requires "
                 << processes[i].getBurstTime() << "ms CPU time)" << endl;
            processes.erase(processes.begin() + i);
            numberOfProcesses--;
            i--;
        }
    }
    return queue;
}

void scheduler::changeInitialStatistics(vector<process>& queue, int systemTime)
{
    int arrivalTime = systemTime - queue[0].getArrivalTime();
    queue[0].setSeenFlag(arrivalTime);
    totalInitialTime += arrivalTime;
    if (arrivalTime < minInitialTime)
        minInitialTime = arrivalTime;
    if (arrivalTime > maxInitialTime)
        maxInitialTime = arrivalTime;
    cout << "[time " << systemTime << "ms] Process "
         << queue[0].getPid() << " accessed CPU for the first time (initial wait time "
         << queue[0].getInitialWaitTime() << "ms)" << endl;
}

void scheduler::changeCompletedStatistics(vector<process>& queue, int systemTime)
{
    int waitTime = ((systemTime + 1) - queue[0].getBurstTime() - queue[0].getArrivalTime());
    cout << "[time " << systemTime + 1
         << "ms] Process " << queue[0].getPid()
         << " completed its CPU burst (turnaround time "
         << ((systemTime + 1) - queue[0].getArrivalTime())
         << "ms, initial wait time " << queue[0].getInitialWaitTime()
         << "ms, total wait time " << waitTime << "ms)" << endl;

    int turn = ((systemTime + 1) - queue[0].getArrivalTime());
    totalTurnaround += turn;
    totalWaitTime += waitTime;
    if (waitTime < minWaitTime)
        minWaitTime = waitTime;
    if (waitTime > maxWaitTime)
        maxWaitTime = waitTime;
    if (turn < minTurnaround)
        minTurnaround = turn;
    if (turn > maxTurnaround)
        maxTurnaround = turn;
}

void scheduler::firstComeFirstServe()
{
    int numberOfCompletedProcesses = 0;
    int systemTime = 0;
    int lastPid = 0;
    vector <process> queue;
    int numberOfProcesses = processes.size();

    while(numberOfCompletedProcesses != numberOfProcesses)
    {
        vector <process> arrivals = getQueueForExequte(processes, systemTime);
        queue.insert(queue.end(), arrivals.begin(), arrivals.end());

        if (queue.size() != 0)
        {
            if (queue[0].hasBeenSeen() == false)
                changeInitialStatistics(queue, systemTime);

            queue[0].decreaseBurstTime();

            if (queue[0].getBurstTimeLeft() == 0)
            {
                changeCompletedStatistics(queue, systemTime);
                lastPid = queue[0].getPid();
                queue.erase(queue.begin());
                numberOfCompletedProcesses++;

                if (queue.size() != 0)
                {
                    cout << "[time " << systemTime + 1 << "ms] Context switch (swapped out process "
                         << lastPid << " for process " << queue[0].getPid() << ")" << endl;

                    systemTime = systemTime + contextSwitch;
                }
            }
        }
        systemTime++;
    }
}

void scheduler::statistics(int numberOfProcesses)
{
    cout << fixed << setprecision(3);
    cout << endl;
    cout << "Turnaround time: min " << minTurnaround
         << "ms; avg " << totalTurnaround / numberOfProcesses
         << "ms; max " << maxTurnaround << "ms" << endl;

    cout << "Initial wait time: min " << minInitialTime
         << "ms; avg " << totalInitialTime / numberOfProcesses
         << "ms; max " << maxInitialTime << "ms" << endl;

    cout << "Total wait time: min " << minWaitTime
         << "ms; avg " << totalWaitTime / numberOfProcesses
         << "ms; max " << maxWaitTime << "ms" << endl << endl;
}



void scheduler::setMinWaitTime(double time)
{
    minWaitTime = time;
}

void scheduler::setMaxWaitTime(double time)
{
    maxWaitTime = time;
}

void scheduler::setMinInitialTime(double time)
{
    minInitialTime = time;
}

void scheduler::setMaxInitialTime(double time)
{
    maxInitialTime = time;
}
