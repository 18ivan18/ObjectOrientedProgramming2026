// c++ -std=c++17 -Wall -Wextra Counter.cpp TwowayCounter.cpp LimitedCounter.cpp LimitedTwowayCounter.cpp Semaphore.cpp main.cpp -o main
#include "Counter.h"
#include "LimitedCounter.h"
#include "LimitedTwowayCounter.h"
#include "Semaphore.h"
#include "TwowayCounter.h"
#include <iostream>

int main()
{
    Counter c(0, 2);
    c.increment();
    c.increment();
    c.increment();
    std::cout << "Counter (step 2): " << c.getTotal() << "\n"; // 6

    TwowayCounter tw(10);
    tw.increment();
    tw.decrement();
    tw.decrement();
    std::cout << "TwowayCounter: " << tw.getTotal() << "\n"; // 9

    LimitedCounter lc(5);
    for (int i = 0; i < 10; i++)
    {
        lc.increment();
    }
    std::cout << "LimitedCounter (max 5): " << lc.getTotal() << "\n"; // 5

    LimitedTwowayCounter ltc(-3, 3, 0, 1);
    for (int i = 0; i < 5; i++)
    {
        ltc.increment();
    }
    std::cout << "LimitedTwowayCounter after 5 increments (max 3): " << ltc.getTotal() << "\n"; // 3
    for (int i = 0; i < 8; i++)
    {
        ltc.decrement();
    }
    std::cout << "LimitedTwowayCounter after 8 decrements (min -3): " << ltc.getTotal() << "\n"; // -3

    Semaphore s;
    std::cout << "Semaphore available: " << s.isAvailable() << "\n"; // 0
    s.signal();
    std::cout << "After signal, available: " << s.isAvailable() << "\n";   // 1
    s.signal();                                                            // capped at max=1
    std::cout << "After second signal (capped): " << s.getTotal() << "\n"; // 1
    s.wait();
    std::cout << "After wait, available: " << s.isAvailable() << "\n"; // 0

    Semaphore s2(true);
    std::cout << "Semaphore(true) available: " << s2.isAvailable() << "\n"; // 1
}
