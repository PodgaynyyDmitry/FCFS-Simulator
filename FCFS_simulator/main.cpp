#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "scheduler.h"

using namespace std;

int main()
{
    int numberOfProcesses = 20;

    scheduler sch(0.0, numberOfProcesses * 5000.0, 0.0, numberOfProcesses * 5000.0);

    sch.createProcesses(numberOfProcesses);

    cout << "First Come First Serve:" << endl << endl;

    sch.simulateFCFS();
    sch.printStatistics(numberOfProcesses);

    return 0;

}
