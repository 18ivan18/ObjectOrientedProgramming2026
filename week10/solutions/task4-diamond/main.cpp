// c++ -std=c++17 -Wall -Wextra ../../../week08/string/String.cpp Animal.cpp Pet.cpp GuideDog.cpp main.cpp -o main
#include "Animal.h"
#include "GuideDog.h"
#include "Pet.h"

int main()
{
    Animal a("Generic animal");
    Pet p("Buddy", "Alice");
    GuideDog g("Rex", "Bob");

    a.describe();
    p.describe();
    g.describe();

    Animal *ptr = &g;
    ptr->describe();
}
