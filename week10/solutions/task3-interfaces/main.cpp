// c++ -std=c++17 -Wall -Wextra Duck.cpp main.cpp -o main
#include "Duck.h"
#include "IFlyable.h"
#include "IRunnable.h"
#include "ISwimmable.h"
#include <iostream>

void makeItFly(IFlyable &f)
{
    f.fly();
}
void makeItSwim(ISwimmable &s)
{
    s.swim();
}
void makeItRun(IRunnable &r)
{
    r.run();
}

int main()
{
    Duck d;

    makeItFly(d);
    makeItSwim(d);
    makeItRun(d);
}
