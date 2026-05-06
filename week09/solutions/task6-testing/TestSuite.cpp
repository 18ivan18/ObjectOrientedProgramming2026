#include "TestSuite.h"
#include <iostream>

static const char *GREEN = "\033[32m";
static const char *RED = "\033[31m";
static const char *YELLOW = "\033[33m";
static const char *BOLD = "\033[1m";
static const char *RESET = "\033[0m";

TestSuite::TestSuite(const char *n) : name(n)
{
}

void TestSuite::setName(const char *newName)
{
    name = String(newName);
}

const char *TestSuite::getName() const
{
    return name.cStr();
}

void TestSuite::add(const TestCase &tc)
{
    tests.pushBack(tc);
}

void TestSuite::run()
{
    for (std::size_t i = 0; i < tests.getSize(); i++)
    {
        tests[i].run();
    }
}

void TestSuite::print() const
{
    std::cout << BOLD << "TestSuite: " << name.cStr() << RESET << "\n";
    for (std::size_t i = 0; i < tests.getSize(); i++)
    {
        const TestCase &tc = tests[i];
        if (tc.isPassed())
        {
            std::cout << GREEN << "[PASS]" << RESET << " " << tc.getName() << "\n";
        }
        else
        {
            std::cout << RED << "[FAIL]" << RESET << " " << tc.getName();
            if (tc.hasError())
            {
                ErrorType t = tc.getErrorType();
                if (t == ErrorType::Warning)
                {
                    std::cout << " " << YELLOW << tc.getErrorMessage() << RESET;
                }
                else
                {
                    std::cout << " " << RED << tc.getErrorMessage() << RESET;
                }
            }
            std::cout << "\n";
        }
    }
}

Vector<TestCase> TestSuite::getPassed() const
{
    Vector<TestCase> result;
    for (std::size_t i = 0; i < tests.getSize(); i++)
    {
        if (tests[i].isPassed())
        {
            result.pushBack(tests[i]);
        }
    }
    return result;
}

Vector<TestCase> TestSuite::getFailed() const
{
    Vector<TestCase> result;
    for (std::size_t i = 0; i < tests.getSize(); i++)
    {
        if (!tests[i].isPassed())
        {
            result.pushBack(tests[i]);
        }
    }
    return result;
}

Vector<TestCase> TestSuite::getByErrorType(ErrorType type) const
{
    Vector<TestCase> result;
    for (std::size_t i = 0; i < tests.getSize(); i++)
    {
        if (tests[i].getErrorType() == type)
        {
            result.pushBack(tests[i]);
        }
    }
    return result;
}

void TestSuite::removeByErrorType(ErrorType type)
{
    Vector<TestCase> filtered;
    for (std::size_t i = 0; i < tests.getSize(); i++)
    {
        if (tests[i].getErrorType() != type)
        {
            filtered.pushBack(tests[i]);
        }
    }
    tests = filtered;
}
