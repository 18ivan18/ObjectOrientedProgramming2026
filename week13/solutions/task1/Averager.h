#ifndef AVERAGER_H
#define AVERAGER_H

#include "Subscriber.h"

class Averager : public Subscriber {
    long long sum;
    int count;
public:
    explicit Averager(const std::string& id);
    void signal(const Message& msg) override;
    double read() const override;
};

#endif // AVERAGER_H
