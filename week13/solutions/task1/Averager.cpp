#include "Averager.h"

Averager::Averager(const std::string& id) : Subscriber(id), sum(0), count(0) {}

void Averager::signal(const Message& msg) {
    sum += msg.data;
    count++;
}

double Averager::read() const {
    if (count == 0) { return 0; }
    return static_cast<double>(sum) / count;
}
