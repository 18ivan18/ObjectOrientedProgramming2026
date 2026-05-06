// c++ -std=c++17 -Wall -Wextra main.cpp -o main
#include "SharedPtr.h"
#include "UniquePtr.h"
#include "WeakPtr.h"
#include <iomanip>
#include <iostream>

struct Foo
{
    int x;
    Foo(int x) : x(x)
    {
    }
    ~Foo()
    {
        std::cout << "~Foo(" << x << ")\n";
    }
};

int main()
{
    {
        UniquePtr<Foo> u(new Foo(10));
        std::cout << u->x << "\n";
        UniquePtr<Foo> u2 = std::move(u);
        std::cout << std::boolalpha << (u.get() == nullptr) << "\n";
    }

    std::cout << "\n";

    SharedPtr<Foo> s1(new Foo(20));
    std::cout << s1.use_count() << "\n";
    {
        SharedPtr<Foo> s2 = s1;
        std::cout << s1.use_count() << "\n";

        WeakPtr<Foo> w = s1;
        std::cout << w.expired() << "\n";
        SharedPtr<Foo> s3 = w.lock();
        std::cout << s3.use_count() << "\n";
    }
    std::cout << s1.use_count() << "\n";
    s1.reset();
}
