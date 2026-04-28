#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"

class Teacher : public Person {
public:
    Teacher() = default;
    Teacher(const String& firstName,
            const String& lastName,
            int age,
            const Address& address,
            int yearsExperience,
            double salary,
            int coursesCount);

    int getYearsExperience() const;
    double getSalary() const;
    int getCoursesCount() const;

    void print(std::ostream& os) const override;

private:
    int yearsExperience = 0;
    double salary = 0.0;
    int coursesCount = 0;
};

#endif // TEACHER_H
