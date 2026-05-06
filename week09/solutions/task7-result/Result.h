#ifndef RESULT_H
#define RESULT_H

#include "Error.h"
#include "Optional.h"

template <typename T> class Result
{
    Optional<T> result;
    Optional<Error> error;

public:
    Result(const T &val) : result(val), error()
    {
    }

    Result(const char *msg) : result(), error(Error(msg))
    {
    }

    bool operator==(const T &) const
    {
        return !result.isNone();
    }

    bool operator==(const Error &) const
    {
        return !error.isNone();
    }

    Optional<T> getResult() const
    {
        return result;
    }

    Optional<Error> getError() const
    {
        return error;
    }
};

#endif // RESULT_H
