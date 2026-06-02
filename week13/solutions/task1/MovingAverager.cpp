#include "MovingAverager.h"
#include <cstring>

MovingAverager::MovingAverager(const std::string& id, size_t ws)
    : Subscriber(id), windowSize(ws), buffer(new int[ws]), head(0), count(0) {}

void MovingAverager::copyFrom(const MovingAverager& other) {
    buffer = new int[windowSize];
    std::memcpy(buffer, other.buffer, windowSize * sizeof(int));
    head = other.head;
    count = other.count;
}

void MovingAverager::clear() {
    delete[] buffer;
    buffer = nullptr;
}

MovingAverager::MovingAverager(const MovingAverager& other)
    : Subscriber(other.id), windowSize(other.windowSize), buffer(nullptr), head(0), count(0) {
    copyFrom(other);
}

MovingAverager::~MovingAverager() {
    clear();
}

void MovingAverager::signal(const Message& msg) {
    buffer[head] = msg.data;
    head = (head + 1) % windowSize;
    if (count < windowSize) { count++; }
}

double MovingAverager::read() const {
    if (count == 0) { return 0; }
    double sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum += buffer[i];
    }
    return sum / static_cast<double>(count);
}
