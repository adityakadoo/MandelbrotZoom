#include <Complex.hpp>
typedef long double ld;

Complex::Complex() : real(ld(0)), imag(ld(0)) {}

Complex::Complex(ld r, ld i) : real(r), imag(i) {}

Complex::~Complex() {}

ld &Complex::operator[](int index)
{
    if (index)
        return imag;
    else
        return real;
}

Complex Complex::operator+(Complex c)
{
    return Complex(real + c[0], imag + c[1]);
}

Complex Complex::operator-(Complex c)
{
    return Complex(real - c[0], imag - c[1]);
}

Complex Complex::operator*(Complex c)
{
    return Complex(real * c[0] - imag * c[1], real * c[1] + imag * c[0]);
}

Complex Complex::operator/(Complex c)
{
    Complex temp((*this) * (!c));
    ld c_abs2 = pow(c.abs(), 2);
    return Complex(temp[0] / c_abs2, temp[1] / c_abs2);
}

ld Complex::abs()
{
    return sqrt(real * real + imag * imag);
}

Complex Complex::operator-()
{
    return Complex(-real, -imag);
}

Complex Complex::operator!()
{
    return Complex(real, -imag);
}

bool Complex::operator==(Complex c)
{
    return real == c[0] && imag == c[1];
}

bool Complex::operator!=(Complex c)
{
    return real != c[0] || imag != c[1];
}
