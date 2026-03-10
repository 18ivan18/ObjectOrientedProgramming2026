#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <exception>
#include <cstring>
#include <iomanip>

enum Course
{
    FIRST = 1,
    SECOND,
    THIRD,
    FOURTH
};

struct Student
{
    char *fn;
    Course course;
    float averageGrade;
};

const int FN_DIGITS = 5;

bool isFnValid(const char *c);
Student initStudent(const char *fn, int course, float avgScore);
void deleteStudent(const Student &s);
void printStudent(const Student &s);

#endif
