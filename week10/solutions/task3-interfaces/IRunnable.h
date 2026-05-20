#ifndef IRUNNABLE_H
#define IRUNNABLE_H

class IRunnable
{
public:
    virtual void run() = 0;
    virtual ~IRunnable() = default;
};

#endif // IRUNNABLE_H
