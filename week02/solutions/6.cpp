#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>

struct Quadratic
{
    double a, b, c, discriminant, x1, x2;
};

void skipSpaces(const char *&p)
{
    while (*p == ' ' || *p == '\t')
        p++;
}

double parseNumber(const char *&p)
{
    double result = 0;
    int sign = 1;
    if (*p == '-')
    {
        sign = -1;
        p++;
    }
    else if (*p == '+')
    {
        p++;
    }
    while (isdigit((unsigned char)*p))
    {
        result = result * 10 + (*p - '0');
        p++;
    }
    if (*p == '.')
    {
        p++;
        double frac = 0.1;
        while (isdigit((unsigned char)*p))
        {
            result += (*p - '0') * frac;
            frac *= 0.1;
            p++;
        }
    }
    return sign * result;
}

double parseCoeff(const char *&p)
{
    skipSpaces(p);
    int sign = 1;
    if (*p == '-')
    {
        sign = -1;
        p++;
    }
    else if (*p == '+')
    {
        p++;
    }
    skipSpaces(p);
    if (!isdigit(*p) && !(*p == '.' && isdigit(*(p + 1))))
        return (double)sign;
    return sign * parseNumber(p);
}

Quadratic fromString(const char *equation)
{
    Quadratic q = {0, 0, 0, 0, 0, 0};
    const char *p1 = strstr(equation, "x^2");
    const char *p2 = p1 ? strstr(p1 + 3, "x") : nullptr;
    const char *p3 = strstr(equation, "=");
    if (!p1 || !p2 || !p3 || p3 <= p2) {
        return q;
    }

    const char *start = equation;
    q.a = parseCoeff(start);

    start = p1 + 3;
    skipSpaces(start);
    if (*start != '+' && *start != '-')
        start = p2;
    q.b = parseCoeff(start);

    start = p2 + 1;
    skipSpaces(start);
    if (*start != '+' && *start != '-')
        start = p3;
    q.c = parseCoeff(start);

    return q;
}

void findRoots(Quadratic &q)
{
    q.discriminant = q.b * q.b - 4 * q.a * q.c;

    if (q.a == 0)
    {
        return;
    }

    if (q.discriminant > 0)
    {
        q.x1 = (-q.b + sqrt(q.discriminant)) / (2 * q.a);
        q.x2 = (-q.b - sqrt(q.discriminant)) / (2 * q.a);
        return;
    }

    if (q.discriminant == 0)
    {
        q.x1 = (-q.b) / (2 * q.a);
        q.x2 = (-q.b) / (2 * q.a);
    }
}

int main()
{
    const char equation[] = "2*x^2 - 12*x + 16 = 0";
    Quadratic q = fromString(equation);
    std::cout << "От уравнение: " << equation << '\n';
    std::cout << "Коефициенти: a=" << q.a << ", b=" << q.b << ", c=" << q.c << '\n';

    if (q.a == 0)
    {
        std::cout << "Не е квадратно уравнение (a не може да е 0).\n";
        return 0;
    }

    findRoots(q);

    if (q.discriminant < 0)
    {
        std::cout << "Няма реални корени (дискриминанта е отрицателна).\n";
        return 0;
    }

    if (q.discriminant == 0)
    {
        std::cout << "Един двоен корен: x = " << q.x1 << '\n';
    }
    else
    {
        std::cout << "Два реални корена: x1 = " << q.x1 << ", x2 = " << q.x2 << '\n';
    }

    std::cout << "\nВъведете коефициенти a, b, c: ";
    std::cin >> q.a >> q.b >> q.c;
    if (q.a == 0)
    {
        std::cout << "Не е квадратно уравнение (a не може да е 0).\n";
        return 0;
    }
    findRoots(q);
    if (q.discriminant < 0)
        std::cout << "Няма реални корени.\n";
    else if (q.discriminant == 0)
        std::cout << "Един двоен корен: x = " << q.x1 << '\n';
    else
        std::cout << "Два реални корена: x1 = " << q.x1 << ", x2 = " << q.x2 << '\n';
}
