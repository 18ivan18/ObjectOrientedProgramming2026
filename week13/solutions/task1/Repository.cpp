#include "Repository.h"

Repository::Repository() : count(0) {}

void Repository::add(Subscriber* s) {
    if (count < MAX_SUBSCRIBERS) {
        subscribers[count++] = s;
    }
}

Subscriber* Repository::get(const std::string& id) const {
    for (int i = 0; i < count; i++) {
        if (subscribers[i]->id == id) { return subscribers[i]; }
    }
    return nullptr;
}

Repository::~Repository() {
    for (int i = 0; i < count; i++) {
        delete subscribers[i];
    }
}
