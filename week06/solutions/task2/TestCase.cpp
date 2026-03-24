#include "TestCase.h"
#include <cstring>

void TestCase::copyFrom(const TestCase& other) {
    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    } else {
        name = nullptr;
    }
    success = other.success;
    error = other.error;
}

void TestCase::free() {
    delete[] name;
    name = nullptr;
}

TestCase::TestCase() : name(nullptr), success(false) {}

TestCase::TestCase(const char* name, bool success, const Error& error)
    : success(success), error(error) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

TestCase::TestCase(const TestCase& other) {
    copyFrom(other);
}

TestCase& TestCase::operator=(const TestCase& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

TestCase::~TestCase() {
    free();
}

const char* TestCase::getName() const {
    return name ? name : "";
}

bool TestCase::isSuccessful() const {
    return success;
}

bool TestCase::hasError() const {
    return error.getType() != ErrorType::None;
}

ErrorType TestCase::getErrorType() const {
    return error.getType();
}

const char* TestCase::getErrorMessage() const {
    return error.getMessage();
}
