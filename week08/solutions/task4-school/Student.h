#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include "Person.h"

#include "../../../utils/Vector.h"

class Student : public Person
{
public:
    Student() = default;
    Student(const String &firstName,
            const String &lastName,
            int age,
            const Address &address,
            const String &facultyNumber,
            const Vector<Course> &courses,
            double averageGrade);

    const String &getFacultyNumber() const;
    const Vector<Course> &getCourses() const;
    double getAverageGrade() const;

    void print(std::ostream &os) const override;

private:
    String facultyNumber;
    Vector<Course> courses;
    double averageGrade = 0.0;
};

#endif // STUDENT_H
