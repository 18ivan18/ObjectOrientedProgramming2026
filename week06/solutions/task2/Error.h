#ifndef ERROR_H
#define ERROR_H

#include <cstddef>

enum class ErrorType {
    None,
    CompilationError,
    Warning,
    ComparisonFailure
};

class Error {
private:
    ErrorType type;
    char* message;

    void copyFrom(const Error& other);
    void free();

public:
    Error();
    Error(ErrorType type, const char* message = nullptr);
    Error(const Error& other);
    Error& operator=(const Error& other);
    ~Error();

    ErrorType getType() const;
    bool hasMessage() const;
    const char* getMessage() const;
};

Error noError();
Error compilationError(const char* message = nullptr);
Error warning(const char* message = nullptr);
Error comparisonFailure(const char* message = nullptr);

#endif
