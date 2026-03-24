#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "TestCase.h"

const size_t MAX_TEST_CASES = 20;

class TestSuite {
private:
    char* name;
    TestCase testCases[MAX_TEST_CASES];
    size_t testCaseCount;

    void copyFrom(const TestSuite& other);
    void free();
    int findTestCaseByName(const char* testName) const;

public:
    TestSuite(const char* name = "");
    TestSuite(const TestSuite& other);
    TestSuite& operator=(const TestSuite& other);
    ~TestSuite();

    void setName(const char* name);
    const char* getName() const;

    bool addTestCase(const TestCase& testCase);

    TestSuite filterPassing() const;
    TestSuite filterFailing() const;
    TestSuite filterByErrorType(ErrorType type) const;

    void removeByErrorType(ErrorType type);

    size_t getTestCaseCount() const;
    const TestCase* getTestCase(size_t index) const;
};

#endif
