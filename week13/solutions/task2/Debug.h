#ifndef DEBUG_H
#define DEBUG_H

#include <string>

class Debug {
public:
    virtual std::string debug_print() const = 0;
    virtual ~Debug() {}
};

#endif // DEBUG_H
