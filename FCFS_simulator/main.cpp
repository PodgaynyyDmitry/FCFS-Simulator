#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "scheduler.h"

using namespace std;

int main()
{
    int numberOfProcesses = 20;

    scheduler sch;

    sch.createProcesses(numberOfProcesses);
    sch.setMaxWaitTime(0.0);
    sch.setMinWaitTime(numberOfProcesses * 5000.0);
    sch.setMaxInitialTime(0.0);
    sch.setMinInitialTime(numberOfProcesses * 5000.0);

    cout << "First Come First Serve:" << endl << endl;

    sch.firstComeFirstServe();
    cout << endl;

    sch.statistics(numberOfProcesses);

    return 0;

}
