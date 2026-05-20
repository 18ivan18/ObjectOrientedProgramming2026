#ifndef IFLYABLE_H
#define IFLYABLE_H

class IFlyable
{
public:
    virtual void fly() = 0;
    virtual ~IFlyable() = default;
};

#endif // IFLYABLE_H
