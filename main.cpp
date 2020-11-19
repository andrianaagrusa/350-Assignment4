#include <iostream>
#include <string>
#include "Simulation.h"
using namespace std;
int main(int argc, char** argv)
{
  Simulation simulation;

  // if user didn't enter a file on the command line
  if(argc < 2)
  {
    cout << "Enter a file in command line (see README)" << endl;
  }

  // user entered a file on the command line
  else if(argc >= 2)
  {
    string file = argv[1];
    int currTime = 0;
    int openWindows = 0;
    bool fileAccepted = true;

    if(simulation.importFile(file)) // take file into the simulation
    {
      while(fileAccepted)
      {
        if(simulation.studentQueue.isEmpty())
        {
          int holdValue = 0;
          for(int i = 0; i < simulation.openWindows; ++i)
          {
              if((simulation.windowArray[i]->windowTime) < 1)
              {
                holdValue++;
              }
          }
          if(holdValue == simulation.openWindows)
          {
            fileAccepted = false;
          }
        }

        // a student in line goes up to a window
        for(int i = 0; i < simulation.openWindows; ++i)
        {
          if(simulation.windowArray[i]->windowTime < 1)
          {
            if(!simulation.studentQueue.isEmpty())
            {
              Student* student = simulation.studentQueue.vFront();
              if(student->entryTime <= currTime)
              {
                if(simulation.windowArray[i]->idleTime > 0)
                {
                  simulation.idleData.enqueue(simulation.windowArray[i]->idleTime);
                }
                simulation.windowArray[i] = simulation.studentQueue.dequeue();
                simulation.waitingData.enqueue(simulation.windowArray[i]->waitTime);
              }
            }
          }
        }

        // increases clock tick each time
        currTime++;
        simulation.clockTick(currTime);
      }

      // tell which windows are empty, increases their idle time
      for(int i = 0; i < simulation.openWindows; ++i)
      {
        if(simulation.windowArray[i]->idleTime > 0)
        {
          simulation.idleData.enqueue(simulation.windowArray[i]->idleTime);
        }
      }

      // outputs
      cout << "The mean student wait time: " << simulation.meanTime() << endl;
      cout << "The median student wait time: " << simulation.medianTime() << endl;
      cout << "The longest student wait time: " << simulation.longestWaitTime() << endl;
      cout << "The number of students waiting over 10 minutes: " << simulation.stuOverTen() << endl;
      cout << "The mean window idle time: " << simulation.meanIdleTime() << endl;
      cout << "The longest window idle time: " << simulation.longestIdleTime() << endl;
      cout << "Number of windows idle for over 5 minutes: " << simulation.idleOverFive() << endl;
    }
  }
  return 0;
}
