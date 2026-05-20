#ifndef COUNTER_H
#define COUNTER_H

class Counter
{
protected:
    int total;
    unsigned step;

public:
    Counter();
    Counter(int initial);
    Counter(int initial, unsigned step);
    virtual void increment();
    int getTotal() const;
    unsigned getStep() const;
    virtual ~Counter() = default;
};

#endif // COUNTER_H
