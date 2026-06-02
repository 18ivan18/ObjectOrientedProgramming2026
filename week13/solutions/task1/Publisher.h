#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Subscriber.h"
#include "Message.h"

class Publisher {
public:
    virtual void subscribe(Subscriber* s) = 0;
    virtual void unsubscribe(Subscriber* s) = 0;
    virtual void signal(const Message& msg) = 0;
    virtual ~Publisher() {}
};

#endif // PUBLISHER_H
