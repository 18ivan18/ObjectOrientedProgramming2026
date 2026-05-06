#ifndef ERROR_H
#define ERROR_H

#include "../../../utils/String.h"

enum class ErrorType
{
    None,
    BuildFailed,
    Warning,
    FailedAssertion
};

class Error
{
private:
    ErrorType type;
    String message;

    Error(ErrorType type, const char *msg);

public:
    static Error newNone();
    static Error newBuildFailed(const char *msg);
    static Error newWarning(const char *msg);
    static Error newFailedAssertion(const char *msg);

    ErrorType getType() const;
    bool hasMessage() const;
    const char *getMessage() const;
    bool isNone() const;
};

#endif // ERROR_H
