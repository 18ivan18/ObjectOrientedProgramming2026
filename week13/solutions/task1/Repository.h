#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Subscriber.h"
#include <string>

class Repository {
    static const int MAX_SUBSCRIBERS = 100;
    Subscriber* subscribers[MAX_SUBSCRIBERS];
    int count;

public:
    Repository();
    void add(Subscriber* s);
    Subscriber* get(const std::string& id) const;
    ~Repository();
};

#endif // REPOSITORY_H
