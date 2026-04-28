#ifndef PERSON_H
#define PERSON_H

#include "Address.h"

#include <iosfwd>

class Person {
public:
    Person() = default;
    Person(const String& firstName, const String& lastName, int age, const Address& address);

    const String& getFirstName() const;
    const String& getLastName() const;
    int getAge() const;
    const Address& getAddress() const;

    virtual void print(std::ostream& os) const;
    virtual ~Person() = default;

private:
    String firstName;
    String lastName;
    int age = 0;
    Address address;
};

#endif // PERSON_H
