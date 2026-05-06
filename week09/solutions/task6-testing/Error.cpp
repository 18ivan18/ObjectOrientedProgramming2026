#include "Error.h"

Error::Error(ErrorType t, const char *msg) : type(t), message(msg ? msg : "")
{
}

Error Error::newNone()
{
    return Error(ErrorType::None, nullptr);
}

Error Error::newBuildFailed(const char *msg)
{
    return Error(ErrorType::BuildFailed, msg);
}

Error Error::newWarning(const char *msg)
{
    return Error(ErrorType::Warning, msg);
}

Error Error::newFailedAssertion(const char *msg)
{
    return Error(ErrorType::FailedAssertion, msg);
}

ErrorType Error::getType() const
{
    return type;
}

bool Error::hasMessage() const
{
    return message.size() > 0;
}

const char *Error::getMessage() const
{
    return message.cStr();
}

bool Error::isNone() const
{
    return type == ErrorType::None;
}
