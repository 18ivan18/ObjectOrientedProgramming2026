#include "PeriodicSampler.h"

PeriodicSampler::PeriodicSampler(const std::string& id, size_t period)
    : Subscriber(id), period(period), lastValue(0), totalReceived(0) {}

void PeriodicSampler::signal(const Message& msg) {
    // First message is always kept. After that, keep every period-th one (n % period == 0).
    if (totalReceived == 0 || totalReceived % period == 0) {
        lastValue = msg.data;
    }
    totalReceived++;
}

double PeriodicSampler::read() const {
    return lastValue;
}
