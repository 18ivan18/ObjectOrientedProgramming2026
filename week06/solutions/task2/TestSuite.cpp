#include "TestSuite.h"
#include <cstring>

void TestSuite::copyFrom(const TestSuite& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    testCaseCount = other.testCaseCount;
    for (size_t i = 0; i < testCaseCount; i++) {
        testCases[i] = other.testCases[i];
    }
}

void TestSuite::free() {
    delete[] name;
}

int TestSuite::findTestCaseByName(const char* testName) const {
    for (size_t i = 0; i < testCaseCount; i++) {
        if (strcmp(testCases[i].getName(), testName) == 0) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

TestSuite::TestSuite(const char* name) : testCaseCount(0) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

TestSuite::TestSuite(const TestSuite& other) {
    copyFrom(other);
}

TestSuite& TestSuite::operator=(const TestSuite& other) {
    if (this != &other) {
        for (size_t i = other.testCaseCount; i < testCaseCount; i++) {
            testCases[i] = TestCase();
        }
        free();
        copyFrom(other);
    }
    return *this;
}

TestSuite::~TestSuite() {
    free();
}


void TestSuite::setName(const char* name) {
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

const char* TestSuite::getName() const {
    return name;
}

bool TestSuite::addTestCase(const TestCase& testCase) {
    if (testCaseCount >= MAX_TEST_CASES) {
        return false;
    }
    if (findTestCaseByName(testCase.getName()) != -1) {
        return false;
    }
    testCases[testCaseCount++] = testCase;
    return true;
}

TestSuite TestSuite::filterPassing() const {
    TestSuite result("");
    for (size_t i = 0; i < testCaseCount; i++) {
        if (testCases[i].isSuccessful()) {
            result.addTestCase(testCases[i]);
        }
    }
    return result;
}

TestSuite TestSuite::filterFailing() const {
    TestSuite result("");
    for (size_t i = 0; i < testCaseCount; i++) {
        if (!testCases[i].isSuccessful()) {
            result.addTestCase(testCases[i]);
        }
    }
    return result;
}

TestSuite TestSuite::filterByErrorType(ErrorType type) const {
    TestSuite result("");
    for (size_t i = 0; i < testCaseCount; i++) {
        if (testCases[i].getErrorType() == type) {
            result.addTestCase(testCases[i]);
        }
    }
    return result;
}

void TestSuite::removeByErrorType(ErrorType type) {
    size_t writeIndex = 0;
    for (size_t i = 0; i < testCaseCount; i++) {
        if (testCases[i].getErrorType() != type) {
            testCases[writeIndex] = testCases[i];
            writeIndex++;
        }
    }
    testCaseCount = writeIndex;
}

size_t TestSuite::getTestCaseCount() const {
    return testCaseCount;
}

const TestCase* TestSuite::getTestCase(size_t index) const {
    if (index >= testCaseCount) {
        return nullptr;
    }
    return &testCases[index];
}
