// Компилиране: g++ -o 4 4.cpp -std=c++14
#include "MyUniquePtr.h"
#include "MySharedPtr.h"
#include "MyWeakPtr.h"
#include <iostream>

struct Resource
{
    int id;
    Resource(int i) : id(i) { std::cout << "Resource(" << id << ") създаден\n"; }
    ~Resource() { std::cout << "Resource(" << id << ") унищожен\n"; }
};

int main()
{
    std::cout << "=== MyUniquePtr ===\n";
    {
        MyUniquePtr<Resource> p1(new Resource(1));
        std::cout << "p1->id = " << p1->id << "\n";

        MyUniquePtr<Resource> p2 = std::move(p1);
        std::cout << "p2->id = " << p2->id << ", use_count след move\n";

        p2.reset(new Resource(2));
    }
    std::cout << "p1, p2 излезли от scope\n\n";

    std::cout << "=== MySharedPtr ===\n";
    {
        MySharedPtr<Resource> sp1(new Resource(10));
        std::cout << "use_count: " << sp1.use_count() << "\n";

        MySharedPtr<Resource> sp2 = sp1;
        std::cout << "use_count след копиране: " << sp1.use_count() << "\n";

        {
            MySharedPtr<Resource> sp3 = sp2;
            std::cout << "use_count в nested scope: " << sp2.use_count() << "\n";
        }
        std::cout << "sp3 излязъл, use_count: " << sp1.use_count() << "\n";
    }
    std::cout << "sp1, sp2 излезли – Resource освободен\n\n";

    std::cout << "=== MyWeakPtr ===\n";
    MyWeakPtr<Resource> wp;
    {
        MySharedPtr<Resource> sp(new Resource(20));
        wp = sp;

        std::cout << "expired преди освобождаване: " << (wp.expired() ? "да" : "не") << "\n";

        if (auto locked = wp.lock())
            std::cout << "lock() успешен, id = " << locked->id << "\n";

        sp.reset();
        std::cout << "expired след sp.reset(): " << (wp.expired() ? "да" : "не") << "\n";

        if (auto locked = wp.lock())
            std::cout << "lock() след reset – не трябва да влезе тук\n";
        else
            std::cout << "lock() върна празен SharedPtr (обектът е унищожен)\n";
    }
    std::cout << "wp все още съществува, но обектът е освободен\n";
}
