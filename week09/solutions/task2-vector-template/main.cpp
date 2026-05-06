// c++ -std=c++17 -Wall -Wextra main.cpp -o main
#include <iostream>

#include "Vector.h"

int main()
{
    Vector<int> a;
    a.pushBack(10);
    a.pushBack(20);
    a.pushBack(30);
    std::cout << a << "\n";
    std::cout << "size=" << a.getSize() << " capacity=" << a.getCapacity() << "\n";

    Vector<int> b = a;
    b.popBack();
    b.pushBack(999);
    std::cout << b << "\n";

    Vector<int> c;
    c.assign(3, 7);
    std::cout << c.getFirst() << " " << c.getLast() << "\n";

    Vector<const char *> s;
    s.pushBack("oop");
    s.pushBack("templates");
    std::cout << s << "\n";

    Vector<int> sum = a + c;
    std::cout << sum << "\n";
}
