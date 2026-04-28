#include "Teacher.h"

#include <ostream>

Teacher::Teacher(const String& firstName,
                 const String& lastName,
                 int age,
                 const Address& address,
                 int yearsExperience,
                 double salary,
                 int coursesCount)
    : Person(firstName, lastName, age, address),
      yearsExperience(yearsExperience),
      salary(salary),
      coursesCount(coursesCount) {}

int Teacher::getYearsExperience() const { return yearsExperience; }
double Teacher::getSalary() const { return salary; }
int Teacher::getCoursesCount() const { return coursesCount; }

void Teacher::print(std::ostream& os) const {
    os << "Teacher{";
    Person::print(os);
    os << ", experienceYears=" << yearsExperience << ", salary=" << salary << ", coursesCount=" << coursesCount
       << "}";
}

