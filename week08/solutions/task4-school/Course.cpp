#include "Course.h"

#include <ostream>

Course::Course(const String& name, const Teacher& teacher, double grade)
    : name(name), teacher(teacher), grade(grade) {}

const String& Course::getName() const { return name; }
const Teacher& Course::getTeacher() const { return teacher; }
double Course::getGrade() const { return grade; }

void Course::print(std::ostream& os) const {
    os << "Course{name=" << name.cStr() << ", teacher=";
    teacher.print(os);
    os << ", grade=" << grade << "}";
}

