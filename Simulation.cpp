#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "Simulation.h"

using namespace std;

// default constructor
Simulation::Simulation()
{
  lineData = 1;
  entryTime = 0;
  timeAtWindow = 0;
  studentClock = 0;

  medianCount = 0;
  idleCount = 0;

  openWindows = 0;
  totalStudents = 0;

  windowArray = NULL;
  idleArray = NULL;
  medianArrary = NULL;
}

//deconstructor
Simulation::~Simulation()
{
  if (windowArray != NULL)
  {
    delete[] windowArray;
  }
  if (idleArray != NULL)
  {
    delete[] idleArray;
  }
  if (medianArrary != NULL)
  {
    delete[] medianArrary;
  }
}

// get and open file
bool Simulation::importFile(string inputfile)
{
  string line;
  int lineNum = 1;
  ifstream file;
  file.open(inputfile.c_str());

  // try/except to read through the file
  try
  {
    getline(file, line); // first line reads num of windows
    openWindows = atoi(line.c_str());
    windowArray = new Student*[openWindows];
    for(int i = 0; i < openWindows; ++i)
    {
      Student* student = new Student();
      windowArray[i] = student;
    }

    lineNum++;
  }

  catch(exception e)
  {
    cout << "ERROR" << endl;
    return false;
  }


  while(getline(file, line)) // second line gets arrival time
  {
    switch(lineData)
    {
      case(1):
      {
        try
        {
          entryTime = atoi(line.c_str());
          lineData++;
          lineNum++;
        }

        catch(exception e)
        {
          cout << "ERROR" << endl;
          return false;
        }
          break;
        }

      case(2):
      {
        try
        {
          if(line != "")
          {
            studentClock = atoi(line.c_str());

            for(int i = 0; i < studentClock; ++i)
            {
              getline(file, line); // third line gets num of students
              lineNum++;
              try {
                  timeAtWindow = atoi(line.c_str());
              }
              catch(exception e) {
                  cout << "ERROR" << endl;
                  return false;
              }
              totalStudents++;
              Student* student = new Student(timeAtWindow, entryTime);
              studentQueue.enqueue(student);
            }
            lineData--;
          }
        }

        catch(exception e)
        {
          cout << "ERROR" << endl;
          return false;
        }
          break;
      }
      default:
      {
        break;
      }
    }
  }
return true;
}

// function for keeping track of clock tick and idle time
bool Simulation::clockTick(int tick)
{
  for(int i = 0; i < openWindows; ++i)
  {
    if(windowArray[i]->windowTime > 0)
    {
      windowArray[i]->windowTime--;
    }
    else
    {
      windowArray[i]->idleTime++;
    }
  }

  // students waiting time increasess
  if(!studentQueue.isEmpty())
  {
    ListNode<Student*> *curr = studentQueue.front;

    while(curr != NULL)
    {
      if(curr->data->entryTime < tick)
      {
        curr->data->waitTime += 1;
      }
      curr = curr->next;
    }
  }
  return true;
}

// median student wait time
double Simulation::medianTime()
{
  ListNode<int> *curr = waitingData.front;

  double medianWaitTime = 0;
  medianCount = 0;

  while(curr != NULL)
  {
    curr = curr->next;
    medianCount++;
  }

  if(medianCount == 0)
  {
    return 0;
  }
  else
  {
    medianArrary = new int[medianCount];
    curr = waitingData.front;

    for(int i = 0; i < medianCount; ++i)
    {
      medianArrary[i] = curr->data;
      curr = curr->next;
    }


    if(medianCount == 1)
    {
      return medianArrary[0];
    }


    else if(medianCount % 2 == 1)
    {
      double d = 0;
      int o = 0;

      o = (medianCount/2);
      d = medianArrary[o];

      return d;
    }

    else
    {
      double d = 0;
      int i = 0;
      int n = 0;

      i = medianCount/2;
      n = (medianCount/2) + 1;

      if(medianArrary[n] == 0)
      {
          return 0;
      }

      d = double(medianArrary[i])/double(medianArrary[n]); // odd num

      return d;
    }
  }
}

// mean student wait time
double Simulation::meanTime()
{
  ListNode<int> *curr = waitingData.front;
  double meanWaitTime = 0.0;
  double sum = 0;
  double count = 0;

  while(curr != NULL)
  {
    sum += curr->data;
    curr = curr->next;
    count++;
  }

  if(count == 0)
  {
    return 0;
  }
  
  meanWaitTime = sum / count;
  return meanWaitTime;
}

// mean window idle time
double Simulation::meanIdleTime()
{
  ListNode<int> *curr = idleData.front;

  double meanIdle = 0;
  double sum = 0;
  double count = 0;

  while(curr != NULL)
  {
    sum += curr->data;
    curr = curr->next;

    count++;
  }

  if(count == 0)
  {
    return 0;
  }

  meanIdle = sum / count;
  return meanIdle;
}

// longest student wait time
int Simulation::longestWaitTime()
{
  if(medianCount == 0)
  {
    return 0;
  }

  else
  {
    return medianArrary[medianCount - 1];
  }
}

// longest window idle time
int Simulation::longestIdleTime()
{
  ListNode<int> *curr = idleData.front;

  idleCount = 0;

  while(curr != NULL)
  {
    curr = curr->next;
    idleCount++;
  }

  idleArray = new int[idleCount];

  curr = idleData.front;

  for(int i = 0; i < idleCount; ++i)
  {
    idleArray[i] = curr->data;
    curr = curr->next;
  }

  return(idleArray[idleCount - 1]);
}

// how many students waited more than 10 minutues
int Simulation::stuOverTen()
{
  if(medianCount == 0)
  {
    return 0;
  }
  else
  {
    int minOverTen = 0;

    for(int i = 0; i < medianCount; ++i)
    {
        if(medianArrary[i] > 10)
        {
          ++minOverTen;
        }
    }
    return minOverTen;
  }
}

// how many windows were idle for longer than 5 minutes
int Simulation::idleOverFive()
{
  int hold = 0;

  for(int i = 0; i < idleCount; ++i)
  {
    if(idleArray[i] > 5)
    {
        ++hold;
    }
  }
  return hold;
}
