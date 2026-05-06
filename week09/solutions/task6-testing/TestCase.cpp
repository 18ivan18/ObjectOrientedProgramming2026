#include "TestCase.h"

TestCase::TestCase() : name(""), error(Error::newNone()), passed(true), testFn(nullptr)
{
}

TestCase::TestCase(const char *n, void (*fn)(TestCase &)) : name(n), error(Error::newNone()), passed(true), testFn(fn)
{
}

void TestCase::run()
{
    passed = true;
    error = Error::newNone();
    if (testFn)
    {
        testFn(*this);
    }
}

void TestCase::assertTrue(bool condition, const char *msg)
{
    if (!passed)
    {
        return;
    }
    if (!condition)
    {
        passed = false;
        error = Error::newFailedAssertion(msg);
    }
}

void TestCase::assertNotNull(const void *ptr, const char *msg)
{
    if (!passed)
    {
        return;
    }
    if (ptr == nullptr)
    {
        passed = false;
        error = Error::newFailedAssertion(msg);
    }
}

bool TestCase::isPassed() const
{
    return passed;
}

bool TestCase::hasError() const
{
    return !error.isNone();
}

ErrorType TestCase::getErrorType() const
{
    return error.getType();
}

const char *TestCase::getErrorMessage() const
{
    return error.getMessage();
}

const char *TestCase::getName() const
{
    return name.cStr();
}
