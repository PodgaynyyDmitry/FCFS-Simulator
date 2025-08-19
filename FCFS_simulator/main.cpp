#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "scheduler.h"

using namespace std;

int main()
{
    int numberOfProcesses = 20;

    Scheduler scheduler(0.0, numberOfProcesses * 5000.0, 0.0, numberOfProcesses * 5000.0);

    scheduler.createProcesses(numberOfProcesses);

    cout << "First Come First Serve:" << endl << endl;

    scheduler.simulateFCFS();
    scheduler.printStatistics(numberOfProcesses);

    string key;
    cout << "Press any key..." << endl;
    cin >> key;

    return 0;
}
