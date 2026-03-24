#include <iostream>
#include "Error.h"
#include "TestCase.h"
#include "TestSuite.h"

int main() {
    TestSuite suite("ООП Задача 1");

    suite.addTestCase(TestCase("testAddDrink", true));
    suite.addTestCase(TestCase("testBuyDrink", false,
                               comparisonFailure("Expected 5, got 4")));
    suite.addTestCase(TestCase("testFillUp", true));
    suite.addTestCase(TestCase("testCompilation", false,
                               compilationError("undefined reference")));
    suite.addTestCase(TestCase("testWarning", false,
                               warning("unused variable")));

    std::cout << "Тестов пакет: " << suite.getName() << std::endl;
    std::cout << "Брой тестове: " << suite.getTestCaseCount() << std::endl;

    std::cout << "\n--- Преминаващи тестове ---" << std::endl;
    TestSuite passing = suite.filterPassing();
    for (size_t i = 0; i < passing.getTestCaseCount(); i++) {
        std::cout << "  " << passing.getTestCase(i)->getName() << std::endl;
    }

    std::cout << "\n--- Непреминаващи тестове ---" << std::endl;
    TestSuite failing = suite.filterFailing();
    for (size_t i = 0; i < failing.getTestCaseCount(); i++) {
        const TestCase* tc = failing.getTestCase(i);
        std::cout << "  " << tc->getName() << " - " << tc->getErrorMessage() << std::endl;
    }

    std::cout << "\n--- Филтриране по ComparisonFailure ---" << std::endl;
    TestSuite compFail = suite.filterByErrorType(ErrorType::ComparisonFailure);
    std::cout << "Намерени: " << compFail.getTestCaseCount() << std::endl;

    std::cout << "\n--- Премахване на CompilationError ---" << std::endl;
    suite.removeByErrorType(ErrorType::CompilationError);
    std::cout << "Останали тестове: " << suite.getTestCaseCount() << std::endl;

    std::cout << "\n--- Error default constructor ---" << std::endl;
    Error defaultErr;
    std::cout << "Default Error type is None: "
              << (defaultErr.getType() == ErrorType::None ? "да" : "не") << std::endl;
    std::cout << "Default Error hasMessage: " << (defaultErr.hasMessage() ? "да" : "не") << std::endl;

    suite.setName("ООП Задача 1 (обновен)");
    std::cout << "\nНово име на пакета: " << suite.getName() << std::endl;
}
