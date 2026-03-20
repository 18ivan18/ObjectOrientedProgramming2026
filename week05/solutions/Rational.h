#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational
{
private:
    int num;
    int den;

    void normalize();

public:
    Rational(int numerator = 0, int denominator = 1);

    int getNumerator() const { return num; }
    int getDenominator() const { return den; }

    Rational operator+(const Rational &rhs) const;
    Rational operator-(const Rational &rhs) const;
    Rational operator*(const Rational &rhs) const;
    Rational operator/(const Rational &rhs) const;

    Rational operator+(int rhs) const;
    Rational operator-(int rhs) const;
    Rational operator*(int rhs) const;
    Rational operator/(int rhs) const;

    friend Rational operator+(int lhs, const Rational &rhs);
    friend Rational operator-(int lhs, const Rational &rhs);
    friend Rational operator*(int lhs, const Rational &rhs);
    friend Rational operator/(int lhs, const Rational &rhs);

    bool operator==(const Rational &rhs) const;
    bool operator!=(const Rational &rhs) const;
    bool operator<(const Rational &rhs) const;
    bool operator<=(const Rational &rhs) const;
    bool operator>(const Rational &rhs) const;
    bool operator>=(const Rational &rhs) const;

    friend bool operator==(int lhs, const Rational &rhs);
    friend bool operator!=(int lhs, const Rational &rhs);
    friend bool operator<(int lhs, const Rational &rhs);
    friend bool operator<=(int lhs, const Rational &rhs);
    friend bool operator>(int lhs, const Rational &rhs);
    friend bool operator>=(int lhs, const Rational &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Rational &r);
};

#endif
