#ifndef COURSE_H
#define COURSE_H

#include "Teacher.h"

class Course {
public:
    Course(const String& name, const Teacher& teacher, double grade);

    const String& getName() const;
    const Teacher& getTeacher() const;
    double getGrade() const;

    void print(std::ostream& os) const;

private:
    String name;
    Teacher teacher;
    double grade = 0.0;
};

#endif // COURSE_H
