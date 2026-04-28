#include "Person.h"

#include <ostream>

Person::Person(const String& firstName, const String& lastName, int age, const Address& address)
    : firstName(firstName), lastName(lastName), age(age), address(address) {}

const String& Person::getFirstName() const { return firstName; }
const String& Person::getLastName() const { return lastName; }
int Person::getAge() const { return age; }
const Address& Person::getAddress() const { return address; }

void Person::print(std::ostream& os) const {
    os << "Person{firstName=" << firstName.cStr() << ", lastName=" << lastName.cStr() << ", age=" << age
       << ", address=";
    address.print(os);
    os << "}";
}

