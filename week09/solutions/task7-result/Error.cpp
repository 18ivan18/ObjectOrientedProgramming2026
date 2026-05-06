#include "Error.h"

Error::Error(const char *msg) : message(msg)
{
}

const char *Error::getMessage() const
{
    return message.cStr();
}
