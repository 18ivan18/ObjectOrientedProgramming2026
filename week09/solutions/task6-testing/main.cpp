// c++ -std=c++17 -Wall -Wextra ../../../week08/string/String.cpp Error.cpp TestCase.cpp TestSuite.cpp main.cpp -o main
#include "TestSuite.h"
#include <iostream>

void testAddition(TestCase &tc)
{
    tc.assertEquals(2 + 2, 4);
    tc.assertEquals(10 - 3, 7);
}

void testStrings(TestCase &tc)
{
    const char *s = "hello";
    tc.assertNotNull(s);
    tc.assertTrue(s[0] == 'h');
}

void testFailingEquality(TestCase &tc)
{
    tc.assertEquals(1 + 1, 3, "1+1 should equal 3");
}

void testNullPointer(TestCase &tc)
{
    int *p = nullptr;
    tc.assertNotNull(p, "pointer must not be null");
}

void testBuildError(TestCase &tc)
{
    tc.assertTrue(false, "simulated build failure");
}

int main()
{
    TestSuite suite("OOP Task Tests");
    suite.add(TestCase("Addition", testAddition));
    suite.add(TestCase("String checks", testStrings));
    suite.add(TestCase("Failing equality", testFailingEquality));
    suite.add(TestCase("Null pointer", testNullPointer));
    suite.add(TestCase("Build error", testBuildError));

    suite.run();
    suite.print();

    std::cout << "\n--- Passed (" << suite.getPassed().getSize() << ") ---\n";
    Vector<TestCase> passed = suite.getPassed();
    for (std::size_t i = 0; i < passed.getSize(); i++)
    {
        std::cout << "  " << passed[i].getName() << "\n";
    }

    std::cout << "\n--- Failed (" << suite.getFailed().getSize() << ") ---\n";
    Vector<TestCase> failed = suite.getFailed();
    for (std::size_t i = 0; i < failed.getSize(); i++)
    {
        std::cout << "  " << failed[i].getName() << ": " << failed[i].getErrorMessage() << "\n";
    }

    suite.removeByErrorType(ErrorType::FailedAssertion);
    std::cout << "\n--- After removing FailedAssertion tests ---\n";
    suite.print();
}
