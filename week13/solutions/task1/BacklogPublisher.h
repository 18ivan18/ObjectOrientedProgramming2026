#ifndef BACKLOG_PUBLISHER_H
#define BACKLOG_PUBLISHER_H

#include "Publisher.h"

class BacklogPublisher : public Publisher {
    static const int MAX_SUBSCRIBERS = 100;
    static const int MAX_BACKLOG = 1000;

    Subscriber* subscribers[MAX_SUBSCRIBERS];
    int backlog[MAX_BACKLOG];
    int subCount;
    int backlogCount;

    int findIndex(const Subscriber* s) const;

public:
    BacklogPublisher();
    void subscribe(Subscriber* s) override;
    void unsubscribe(Subscriber* s) override;
    void signal(const Message& msg) override;
};

#endif // BACKLOG_PUBLISHER_H
