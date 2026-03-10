#include "Complex.h"
#include <iostream>

void Complex::setReal(double real)
{
    this->real = real;
}

void Complex::setImaginary(double imaginary)
{
    this->imaginary = imaginary;
}

double Complex::getReal() const
{
    return real;
}

double Complex::getImaginary() const
{
    return imaginary;
}

Complex Complex::add(const Complex &other) const
{
    return {real + other.real, imaginary + other.imaginary};
}

Complex Complex::multiply(const Complex &other) const
{
    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    return {real * other.real - imaginary * other.imaginary,
                   real * other.imaginary + imaginary * other.real};
}

void Complex::print() const
{
    std::cout << real;
    if (imaginary >= 0)
        std::cout << " + " << imaginary;
    else
        std::cout << " - " << -imaginary;
    std::cout << "i\n";
}

Complex Complex::conjugate() const
{
    return {real, -imaginary};
}