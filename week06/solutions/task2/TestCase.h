#ifndef TEST_CASE_H
#define TEST_CASE_H

#include "Error.h"

class TestCase {
private:
    char* name;
    bool success;
    Error error;

    void copyFrom(const TestCase& other);
    void free();

public:
    TestCase();
    TestCase(const char* name, bool success, const Error& error = Error());
    TestCase(const TestCase& other);
    TestCase& operator=(const TestCase& other);
    ~TestCase();

    const char* getName() const;
    bool isSuccessful() const;
    bool hasError() const;
    ErrorType getErrorType() const;
    const char* getErrorMessage() const;
};

#endif
