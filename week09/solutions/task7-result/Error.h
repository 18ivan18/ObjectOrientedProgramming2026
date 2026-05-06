#ifndef ERROR_H
#define ERROR_H

#include "../../../utils/String.h"

class Error
{
    String message;

public:
    Error(const char *msg = "");
    const char *getMessage() const;
};

#endif // ERROR_H
