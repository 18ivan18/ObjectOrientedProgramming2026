#ifndef TESTCASE_H
#define TESTCASE_H

#include "../../../utils/String.h"
#include "Error.h"

class TestCase
{
private:
    String name;
    Error error;
    bool passed;
    void (*testFn)(TestCase &);

public:
    TestCase();
    TestCase(const char *name, void (*fn)(TestCase &));

    void run();

    void assertTrue(bool condition, const char *msg = "assertTrue failed");
    void assertNotNull(const void *ptr, const char *msg = "assertNotNull failed");

    template <typename T> void assertEquals(const T &a, const T &b, const char *msg = "assertEquals failed")
    {
        if (!passed)
        {
            return;
        }
        if (!(a == b))
        {
            passed = false;
            error = Error::newFailedAssertion(msg);
        }
    }

    bool isPassed() const;
    bool hasError() const;
    ErrorType getErrorType() const;
    const char *getErrorMessage() const;
    const char *getName() const;
};

#endif // TESTCASE_H
