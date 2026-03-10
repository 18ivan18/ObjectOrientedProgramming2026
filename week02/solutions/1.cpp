#include <iostream>

struct Complex
{
    float real, imaginary;
};

void print(const Complex &c)
{
    std::cout << c.real << " + " << (c.imaginary < 0 ? "(" : "") << c.imaginary << (c.imaginary < 0 ? ")" : "") << "i\n";
}

Complex add(const Complex &first, const Complex &second)
{
    return {first.real + second.real, first.imaginary + second.imaginary};
}

Complex multiply(const Complex &first, const Complex &second)
{
    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    return {first.real * second.real - first.imaginary * second.imaginary,
            first.real * second.imaginary + first.imaginary * second.real};
}

Complex conjugate(const Complex &c)
{
    // комплексно спрегнато на a + bi е a - bi
    return {c.real, -c.imaginary};
}

int main()
{
    Complex a{5, -3.14};
    print(a);
    Complex b{10, 4.15};
    print(b);
    print(add(a, b));
    print(multiply(a, b));
    print(conjugate(a));
}