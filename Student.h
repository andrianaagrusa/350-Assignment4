// good
#include <iostream>

using namespace std;

class Student
{
public:
    Student();
    Student(int wT, int eT);
    ~Student();

    int entryTime;
    int windowTime;

    int waitTime;
    int idleTime;
};
