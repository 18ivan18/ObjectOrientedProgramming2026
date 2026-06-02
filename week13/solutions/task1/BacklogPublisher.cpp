#include "BacklogPublisher.h"

BacklogPublisher::BacklogPublisher() : subCount(0), backlogCount(0) {}

int BacklogPublisher::findIndex(const Subscriber* s) const {
    for (int i = 0; i < subCount; i++) {
        if (subscribers[i]->id == s->id) { return i; }
    }
    return -1;
}

void BacklogPublisher::subscribe(Subscriber* s) {
    if (findIndex(s) != -1 || subCount >= MAX_SUBSCRIBERS) { return; }
    subscribers[subCount++] = s;
    for (int i = 0; i < backlogCount; i++) {
        s->signal(Message(backlog[i]));
    }
}

void BacklogPublisher::unsubscribe(Subscriber* s) {
    int idx = findIndex(s);
    if (idx == -1) { return; }
    for (int i = idx; i < subCount - 1; i++) {
        subscribers[i] = subscribers[i + 1];
    }
    subCount--;
}

void BacklogPublisher::signal(const Message& msg) {
    if (backlogCount < MAX_BACKLOG) {
        backlog[backlogCount++] = msg.data;
    }
    for (int i = 0; i < subCount; i++) {
        subscribers[i]->signal(msg);
    }
}
