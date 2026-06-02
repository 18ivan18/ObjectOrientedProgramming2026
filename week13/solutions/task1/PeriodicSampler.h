#ifndef PERIODIC_SAMPLER_H
#define PERIODIC_SAMPLER_H

#include "Subscriber.h"
#include <cstddef>

class PeriodicSampler : public Subscriber {
    size_t period;
    int lastValue;
    size_t totalReceived;
public:
    PeriodicSampler(const std::string& id, size_t period);
    void signal(const Message& msg) override;
    double read() const override;
};

#endif // PERIODIC_SAMPLER_H
