#ifndef MOVING_AVERAGER_H
#define MOVING_AVERAGER_H

#include "Subscriber.h"
#include <cstddef>

class MovingAverager : public Subscriber {
public:
    const size_t windowSize;

private:
    int* buffer;
    size_t head;
    size_t count;

    void copyFrom(const MovingAverager& other);
    void clear();

public:
    MovingAverager(const std::string& id, size_t windowSize);
    MovingAverager(const MovingAverager& other);
    MovingAverager& operator=(const MovingAverager&) = delete;
    ~MovingAverager();

    void signal(const Message& msg) override;
    double read() const override;
};

#endif // MOVING_AVERAGER_H
