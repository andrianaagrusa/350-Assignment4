

#include <iostream>
#include <string>
#include "Student.h"
#include "GenQueue.h"

using namespace std;

class Simulation
{
public:
    Simulation();
    ~Simulation();
    bool importFile(string inputfile);
    bool clockTick(int tick);

    double meanTime();
    double medianTime();
    int longestWaitTime();
    int stuOverTen();

    double meanIdleTime();
    int longestIdleTime();
    int idleOverFive();

    Student **windowArray;

    GenQueue<Student*> studentQueue;
    GenQueue<int> waitingData;
    GenQueue<int> idleData;
    int openWindows;
    int totalStudents;
    int *medianArrary;
    int *idleArray;

private:
    int lineData;
    int entryTime;
    int timeAtWindow;
    int studentClock;
    int medianCount;
    int idleCount;

};
