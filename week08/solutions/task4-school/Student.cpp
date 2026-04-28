#include "Student.h"

#include <ostream>

Student::Student(const String& firstName,
                 const String& lastName,
                 int age,
                 const Address& address,
                 const String& facultyNumber,
                 const std::vector<Course>& courses,
                 double averageGrade)
    : Person(firstName, lastName, age, address),
      facultyNumber(facultyNumber),
      courses(courses),
      averageGrade(averageGrade) {}

const String& Student::getFacultyNumber() const { return facultyNumber; }
const std::vector<Course>& Student::getCourses() const { return courses; }
double Student::getAverageGrade() const { return averageGrade; }

void Student::print(std::ostream& os) const {
    os << "Student{";
    Person::print(os);
    os << ", fn=" << facultyNumber.cStr() << ", avg=" << averageGrade << ", courses=[";
    for (std::size_t i = 0; i < courses.size(); ++i) {
        if (i != 0) os << ", ";
        courses[i].print(os);
    }
    os << "]}";
}

