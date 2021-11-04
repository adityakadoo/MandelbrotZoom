#ifndef __COMPLEX__
#define __COMPLEX__
#include <iostream>
#include <math.h>

template<typename f>
class Complex
{
private:
    // template argument defines precision of
    // the real and imag components
    f real;
    f imag;
public:
    /* Constructors and Destructors */
    // Default constructor; returns origin
    Complex();
    // Constructor with real and imag components
    Complex(f, f);
    // Default destructor
    ~Complex();
    
    /* Component Access */
    // Read/write refererence for real or imag components
    // [0] - real; [1] - imag
    f& operator[](int);

    /* Arithmetic Operations */
    // Addition
    Complex<f> operator+(Complex<f>&);
    // Subraction
    Complex<f> operator-(Complex<f>&);
    // Multiplication
    Complex<f> operator*(Complex<f>&);
    // Division
    Complex<f> operator/(Complex<f>&);
    // Absolute value or Magnitude
    f abs();
    // Negative
    Complex<f> operator-();
    // Compliment
    Complex<f> operator!();
    
    /* Boolean Operations */
    // Equality
    bool operator==(Complex<f>&);
    // Inequality
    bool operator!=(Complex<f>&);

    /* Printing */
    // Prints the given complex number
    friend std::ostream& operator<<(std::ostream &cout, Complex<f> &c){
        cout<<c.real<<"+"<<c.imag<<"j";
        return cout;
    }
};

#endif