#ifndef ISWIMMABLE_H
#define ISWIMMABLE_H

class ISwimmable
{
public:
    virtual void swim() = 0;
    virtual ~ISwimmable() = default;
};

#endif // ISWIMMABLE_H
