#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
// private:
public:
    double real = 0;
    double imaginary = 0;

public:
    void setReal(double);
    void setImaginary(double);
    double getReal() const;
    double getImaginary() const;

    Complex add(const Complex &other) const;
    Complex multiply(const Complex &other) const;
    Complex conjugate() const;

    void print() const;
};

#endif
