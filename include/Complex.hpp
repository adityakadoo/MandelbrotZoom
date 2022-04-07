#ifndef __COMPLEX__
#define __COMPLEX__
#include <iostream>
#include <iomanip>
#include <math.h>

#define MAX_ERR 1e-6

class Complex
{
private:
    // template argument defines precision of
    // the real and imag components
    long double real;
    long double imag;

public:
    /* Constructors and Destructors */
    // Default constructor; returns origin
    Complex();
    // Constructor with real and imag components
    Complex(long double, long double);
    // Default destructor
    ~Complex();

    /* Component Access */
    // Read/write refererence for real or imag components
    // [0] - real; [1] - imag
    long double &operator[](int);

    /* Arithmetic Operations */
    // Addition
    Complex operator+(Complex);
    // Subraction
    Complex operator-(Complex);
    // Multiplication
    Complex operator*(Complex);
    // Division
    Complex operator/(Complex);
    // Absolute value or Magnitude
    long double abs();
    // Negative
    Complex operator-();
    // Compliment
    Complex operator!();

    /* Boolean Operations */
    // Equality
    bool operator==(Complex);
    // Inequality
    bool operator!=(Complex);

    /* Printing */
    // Prints the given complex number
    friend std::ostream &operator<<(std::ostream &cout, Complex &c)
    {
        if (c.imag >= 0)
        {
            cout << std::fixed << std::setprecision(4) << c.real << "+" << c.imag << "j";
        }
        else
        {
            cout << std::fixed << std::setprecision(4) << c.real << c.imag << "j";
        }
        return cout;
    }
};

#endif