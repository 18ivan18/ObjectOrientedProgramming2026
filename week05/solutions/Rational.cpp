#include "Rational.h"
#include <cstdlib>

int rationalGcd(int a, int b)
{
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

Rational::Rational(int numerator, int denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    num = numerator;
    den = denominator;
    normalize();
}

void Rational::normalize()
{
    if (den < 0)
    {
        num = -num;
        den = -den;
    }
    int g = rationalGcd(num, den);
    if (g != 0)
    {
        num /= g;
        den /= g;
    }
    if (den == 0)
        den = 1;
}

Rational Rational::operator+(const Rational &rhs) const
{
    int n = num * rhs.den + rhs.num * den;
    int d = den * rhs.den;
    Rational result(n, d);
    return result;
}

Rational Rational::operator-(const Rational &rhs) const
{
    int n = num * rhs.den - rhs.num * den;
    int d = den * rhs.den;
    Rational result(n, d);
    return result;
}

Rational Rational::operator*(const Rational &rhs) const
{
    int n = num * rhs.num;
    int d = den * rhs.den;
    Rational result(n, d);
    return result;
}

Rational Rational::operator/(const Rational &rhs) const
{
    if (rhs.num == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    int n = num * rhs.den;
    int d = den * rhs.num;
    if (d < 0)
    {
        n = -n;
        d = -d;
    }
    Rational result(n, d);
    return result;
}

Rational Rational::operator+(int rhs) const
{
    return *this + Rational(rhs, 1);
}

Rational Rational::operator-(int rhs) const
{
    return *this - Rational(rhs, 1);
}

Rational Rational::operator*(int rhs) const
{
    return *this * Rational(rhs, 1);
}

Rational Rational::operator/(int rhs) const
{
    return *this / Rational(rhs, 1);
}

Rational operator+(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) + rhs;
}

Rational operator-(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) - rhs;
}

Rational operator*(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) * rhs;
}

Rational operator/(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) / rhs;
}

bool Rational::operator==(const Rational &rhs) const
{
    return num == rhs.num && den == rhs.den;
}

bool Rational::operator!=(const Rational &rhs) const
{
    return !(*this == rhs);
}

bool Rational::operator<(const Rational &rhs) const
{
    return num * rhs.den < rhs.num * den;
}

bool Rational::operator<=(const Rational &rhs) const
{
    return *this < rhs || *this == rhs;
}

bool Rational::operator>(const Rational &rhs) const
{
    return rhs < *this;
}

bool Rational::operator>=(const Rational &rhs) const
{
    return *this > rhs || *this == rhs;
}

bool operator==(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) == rhs;
}

bool operator!=(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) != rhs;
}

bool operator<(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) < rhs;
}

bool operator<=(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) <= rhs;
}

bool operator>(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) > rhs;
}

bool operator>=(int lhs, const Rational &rhs)
{
    return Rational(lhs, 1) >= rhs;
}

std::ostream &operator<<(std::ostream &os, const Rational &r)
{
    os << r.num << "/" << r.den;
    return os;
}
