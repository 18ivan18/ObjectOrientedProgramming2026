#include "Course.h"
#include "Student.h"
#include "Teacher.h"

#include <iostream>
#include <vector>

int main() {
    Address teacherAddress{"Sofia", "Tsarigradsko shose 1"};
    Teacher t("Ivan", "Ivanov", 42, teacherAddress, 15, 3500.0, 2);

    Course oop("OOP", t, 5.75);
    Course math("Math", t, 5.25);

    Address studentAddress{"Sofia", "Studentski grad 10"};
    Student s("Maria", "Petrova", 20, studentAddress, "0MI0800000", std::vector<Course>{oop, math}, 5.50);

    std::cout << "Task 4 demo\n";
    t.print(std::cout);
    std::cout << "\n";
    s.print(std::cout);
    std::cout << "\n";
}

