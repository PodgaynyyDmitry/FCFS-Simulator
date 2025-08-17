#include "scheduler.h"
#include <time.h>
#include <cmath>
#include <iostream>

using namespace std;
scheduler::scheduler() {}

void scheduler::createZeroArrivalTimeProcesses(vector<process>& processe, int num_zero)
{
    int random_burst;
    int importance;
    for (int i = 0; i < num_zero; i++)
    {
        random_burst = (rand()%3500)+500;
        importance = (rand()%5);
        process temp(random_burst, 0, i+1, importance);
        processes.push_back(temp);
    }
}

void scheduler::createProcesses(vector<process>& processe, int num_rand, int num_zero)
{
    int random_burst;
    int importance;
    for(int i = 0; i < num_rand; i++)
    {
        random_burst = (rand()%3500)+500;
        importance = (rand()%5);
        double lambda = 0.001;
        double r = ((double) rand()/(RAND_MAX));
        double x = -(log(r)/lambda);
        if ( x > 8000 ) { i--; continue; }
        process temp(random_burst, (int)x, (num_zero + i+1), importance);
        processes.push_back(temp);
    }
}

void scheduler::createProcesses(int numberOfProcesses)
{
    srand((unsigned)time(0));
    int num_rand = numberOfProcesses * .8;
    int num_zero = numberOfProcesses - num_rand;
    createZeroArrivalTimeProcesses(processes, num_zero);
    createProcesses(processes, num_rand, num_zero);
}

vector<process> scheduler::getQueueForExequte(vector<process>& processes, int clock)
{
    int index = processes.size();
    vector <process> queue;

    for(unsigned int i = 0; i < index; i++)
    {
        if (processes[i].getArrivalTime() <= clock)
        {
            queue.push_back(processes[i]);
            cout << "[time " << processes[i].getArrivalTime() << "ms] Process "
                 << processes[i].getPid() << " created (requires "
                 << processes[i].getBurstTime() << "ms CPU time)" << endl;
            processes.erase(processes.begin() + i);
            index--;
            i--;
        }
    }
    return queue;
}

void scheduler::changeInitialStatistics(vector<process>& queue, int clock)
{
    int arriv = clock - queue[0].getArrivalTime();
    queue[0].setSeenFlag(arriv);
    totalInitialTime += arriv;
    if (arriv < minInitialTime)
        minInitialTime = arriv;
    if (arriv > maxInitialTime)
        maxInitialTime = arriv;
    cout << "[time " << clock << "ms] Process "
         << queue[0].getPid() << " accessed CPU for the first time (initial wait time "
         << queue[0].getInitialWaitTime() << "ms)" << endl;
}

void scheduler::changeCompletedStatistics(vector<process>& queue, int clock)
{
    int fwait = ((clock + 1) - queue[0].getBurstTime() - queue[0].getArrivalTime());
    cout << "[time " << clock + 1
         << "ms] Process " << queue[0].getPid()
         << " completed its CPU burst (turnaround time "
         << ((clock + 1) - queue[0].getArrivalTime())
         << "ms, initial wait time " << queue[0].getInitialWaitTime()
         << "ms, total wait time " << fwait << "ms)" << endl;

    int turn = ((clock + 1) - queue[0].getArrivalTime());
    totalTurnaround += turn;
    if (fwait < minWaitTime)
        minWaitTime = fwait;
    if (fwait > maxWaitTime)
        maxWaitTime = fwait;
    if (turn < minTurnaround)
        minTurnaround = turn;
    if (turn > maxTurnaround)
        maxTurnaround = turn;
}

void scheduler::firstComeFirstServe()
{
    int num_completed = 0;
    int clock = 0;
    int last_pid = 0;
    vector <process> queue;
    bool cswitch = false;
    int num_processes = processes.size();

    while(num_completed != num_processes)
    {
        vector <process> arrivals = getQueueForExequte(processes, clock);
        queue.insert(queue.end(), arrivals.begin(), arrivals.end());

        if (queue.size() != 0)
        {
            if (queue[0].hasBeenSeen() == false)
                changeInitialStatistics(queue, clock);

            queue[0].decreaseBurstTime();

            // Содержимое тоже вынести в отдельный метод
            if (queue[0].getBurstTimeLeft() == 0)
            {
                changeCompletedStatistics(queue, clock);
                last_pid = queue[0].getPid();
                queue.erase(queue.begin());
                num_completed++;

                if (queue.size() != 0)
                {
                    cout << "[time " << clock + 1 << "ms] Context switch (swapped out process "
                         << last_pid << " for process " << queue[0].getPid() << ")" << endl;

                    clock = clock + contextSwitch;
                }
            }
        }
        clock++;
    }
}

void scheduler::statistics(int numberOfProcesses)
{
    cout << "Turnaround time: min ";
    printf("%.3f", minTurnaround);
    cout << "ms";
    cout << "; avg ";
    printf("%.3f", totalTurnaround/numberOfProcesses);
    cout << "ms";
    cout << "; max ";
    printf("%.3f", maxTurnaround);
    cout << "ms" << endl;
    cout << "Initial wait time: min ";
    printf("%.3f", minInitialTime);
    cout << "ms";
    cout << "; avg ";
    printf("%.3f", totalInitialTime/numberOfProcesses);
    cout << "ms";
    cout << "; max ";
    printf("%.3f", maxInitialTime);
    cout << "ms" << endl;
    cout << "Total wait time: min ";
    printf("%.3f", minWaitTime);
    cout << "ms";
    cout << "; avg ";
    printf("%.3f", (maxWaitTime + minWaitTime)/numberOfProcesses);
    cout << "ms";
    cout << "; max ";
    printf("%.3f", maxWaitTime);
    cout << "ms" << endl;
    cout << endl;
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
