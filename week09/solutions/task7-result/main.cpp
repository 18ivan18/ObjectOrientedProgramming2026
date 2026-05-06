// c++ -std=c++17 -Wall -Wextra ../../../week08/string/String.cpp Error.cpp main.cpp -o main
#include "Result.h"
#include <iostream>

int main()
{
    // examples from the task
    std::cout << std::boolalpha << (Result<int>(3) == int()) << "\n"; // 1 (has value)
    std::cout << (Result<int>(5) == Error()) << "\n";                 // 0 (no error)
    std::cout << (Result<int>("Error Message") == Error()) << "\n";   // 1 (has error)

    std::cout << "\n";

    // getResult / getError
    Result<int> ok(42);
    Optional<int> val = ok.getResult();
    std::cout << val.isNone() << "\n";   // 0
    std::cout << val.getValue() << "\n"; // 42

    Optional<Error> noErr = ok.getError();
    std::cout << noErr.isNone() << "\n"; // 1

    std::cout << "\n";

    Result<int> failed("division by zero");
    Optional<int> noVal = failed.getResult();
    std::cout << noVal.isNone() << "\n";   // 1
    std::cout << noVal.getValue() << "\n"; // 0 (default int)

    Optional<Error> err = failed.getError();
    std::cout << err.isNone() << "\n";                // 0
    std::cout << err.getValue().getMessage() << "\n"; // division by zero
}
