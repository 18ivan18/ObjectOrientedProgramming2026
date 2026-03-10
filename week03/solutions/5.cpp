// Компилиране: g++ -o 5 5.cpp Vector.cpp
#include "Vector.h"
#include <iostream>

int main()
{
    Vector v(3);

    std::cout << "isEmpty: " << (v.isEmpty() ? "true" : "false") << '\n';
    std::cout << "capacity: " << v.getCapacity() << ", size: " << v.getSize() << '\n';

    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    std::cout << "\nСлед pushBack(1,2,3): capacity=" << v.getCapacity() << ", size=" << v.getSize() << '\n';
    std::cout << "getFirst=" << v.getFirst() << ", getLast=" << v.getLast() << '\n';

    v.pushBack(4);
    std::cout << "\nСлед pushBack(4): capacity=" << v.getCapacity() << ", size=" << v.getSize() << '\n';

    v.assign(5, 10);
    std::cout << "\nСлед assign(5, 10): capacity=" << v.getCapacity() << ", size=" << v.getSize() << '\n';
    std::cout << "getAt(2)=" << v.getAt(2) << '\n';

    v.popBack();
    v.popBack();
    std::cout << "\nСлед 2x popBack: size=" << v.getSize() << '\n';

    v.removeAt(0);
    std::cout << "След removeAt(0): size=" << v.getSize() << ", getFirst=" << v.getFirst() << '\n';
}
