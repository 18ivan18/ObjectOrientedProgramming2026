#ifndef SIMPLE_PUBLISHER_H
#define SIMPLE_PUBLISHER_H

#include "Publisher.h"

class SimplePublisher : public Publisher {
    static const int MAX_SUBSCRIBERS = 100;
    Subscriber* subscribers[MAX_SUBSCRIBERS];
    int count;

    int findIndex(const Subscriber* s) const;

public:
    SimplePublisher();
    void subscribe(Subscriber* s) override;
    void unsubscribe(Subscriber* s) override;
    void signal(const Message& msg) override;
};

#endif // SIMPLE_PUBLISHER_H
