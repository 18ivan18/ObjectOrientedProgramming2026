#include "SimplePublisher.h"

SimplePublisher::SimplePublisher() : count(0) {}

int SimplePublisher::findIndex(const Subscriber* s) const {
    for (int i = 0; i < count; i++) {
        if (subscribers[i]->id == s->id) { return i; }
    }
    return -1;
}

void SimplePublisher::subscribe(Subscriber* s) {
    if (findIndex(s) == -1 && count < MAX_SUBSCRIBERS) {
        subscribers[count++] = s;
    }
}

void SimplePublisher::unsubscribe(Subscriber* s) {
    int idx = findIndex(s);
    if (idx == -1) { return; }
    for (int i = idx; i < count - 1; i++) {
        subscribers[i] = subscribers[i + 1];
    }
    count--;
}

void SimplePublisher::signal(const Message& msg) {
    for (int i = 0; i < count; i++) {
        subscribers[i]->signal(msg);
    }
}
