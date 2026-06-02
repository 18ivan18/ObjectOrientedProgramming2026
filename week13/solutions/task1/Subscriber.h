#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <string>
#include "Message.h"

class Subscriber {
public:
    const std::string id;

    explicit Subscriber(const std::string& id) : id(id) {}
    virtual void signal(const Message& msg) = 0;
    virtual double read() const = 0;
    virtual ~Subscriber() {}
};

#endif // SUBSCRIBER_H
