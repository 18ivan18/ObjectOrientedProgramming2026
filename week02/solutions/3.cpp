// Компилиране: g++ -o 3 3.cpp Group.cpp Student.cpp
#include "Group.h"

int main()
{
    Group g = initGroupFromStdIn();
    scolarship(g, 5.50f);
    std::cout << g.avgGrade << '\n';
    deleteGroup(g);
}