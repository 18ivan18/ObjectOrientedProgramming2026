#ifndef GROUP_H
#define GROUP_H

#include "Student.h"

struct Group
{
    int numberOfStudentsInGroup;
    Student *students;
    float avgGrade;
};

Group initGroupFromStdIn();
void deleteGroup(const Group &g);
void scolarship(const Group &g, float grade);

#endif
