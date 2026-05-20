// c++ -std=c++17 -Wall -Wextra ../../../week08/string/String.cpp Employee.cpp Manager.cpp Intern.cpp main.cpp -o main
#include "Employee.h"
#include "Intern.h"
#include "Manager.h"

int main()
{
    const int len = 5;
    Employee *team[len] = {
        new Employee("Alice"),   new Manager("Bob", 5),         new Intern("Carol", "FMI"),
        new Manager("Dave", 12), new Intern("Eve", "TU Sofia"),
    };

    for (int i = 0; i < len; i++)
    {
        team[i]->describe();
        delete team[i];
    }
}
