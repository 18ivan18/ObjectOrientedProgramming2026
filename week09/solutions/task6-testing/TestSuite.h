#ifndef TESTSUITE_H
#define TESTSUITE_H

#include "../../../utils/String.h"
#include "../../../utils/Vector.h"
#include "TestCase.h"

class TestSuite
{
private:
    String name;
    Vector<TestCase> tests;

public:
    TestSuite(const char *name);

    void setName(const char *newName);
    const char *getName() const;

    void add(const TestCase &tc);
    void run();
    void print() const;

    Vector<TestCase> getPassed() const;
    Vector<TestCase> getFailed() const;
    Vector<TestCase> getByErrorType(ErrorType type) const;
    void removeByErrorType(ErrorType type);
};

#endif // TESTSUITE_H
