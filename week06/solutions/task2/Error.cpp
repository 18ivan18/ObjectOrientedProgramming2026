#include "Error.h"
#include <cstring>

void Error::copyFrom(const Error& other) {
    type = other.type;
    if (other.message) {
        message = new char[strlen(other.message) + 1];
        strcpy(message, other.message);
    } else {
        message = nullptr;
    }
}

void Error::free() {
    delete[] message;
}

Error::Error() : type(ErrorType::None), message(nullptr) {}

Error::Error(ErrorType type, const char* message) : type(type) {
    if (message && message[0] != '\0') {
        this->message = new char[strlen(message) + 1];
        strcpy(this->message, message);
    } else {
        this->message = nullptr;
    }
}

Error::Error(const Error& other) {
    copyFrom(other);
}

Error& Error::operator=(const Error& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Error::~Error() {
    free();
}

ErrorType Error::getType() const {
    return type;
}

bool Error::hasMessage() const {
    return message != nullptr && message[0] != '\0';
}

const char* Error::getMessage() const {
    return message ? message : "";
}

Error noError() {
    return Error();
}

Error compilationError(const char* message) {
    return Error(ErrorType::CompilationError, message);
}

Error warning(const char* message) {
    return Error(ErrorType::Warning, message);
}

Error comparisonFailure(const char* message) {
    return Error(ErrorType::ComparisonFailure, message);
}
