#include <Mandelbrot.hpp>
typedef long long int ll;
typedef unsigned long int usi;
typedef long double ld;

ld mandelbrot(Complex c, ll max_iter)
{
    Complex z;
    ld it = 0;
    while (z.abs() <= 2 && it < max_iter)
    {
        z = z * z + c;
        it += 1;
    }
    return it == max_iter ? it : it + 1 - log(log2(z.abs()));
}
