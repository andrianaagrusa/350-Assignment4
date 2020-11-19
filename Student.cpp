//good
#include <iostream>
#include "Student.h"

using namespace std;

Student::Student() // default constructor
{
  windowTime = 0;
  entryTime = 0;
  waitTime = 0;
  idleTime = 0;
}

Student::Student(int wT, int eT) // overloaded constructor
{
  windowTime = wT;
  entryTime = eT;

  waitTime = 0;
  idleTime = 0;
}

Student::~Student() {} // deconstructor
