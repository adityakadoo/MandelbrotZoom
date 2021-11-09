#include <Mandelbrot.hpp>
typedef long long int ll;
typedef unsigned long int usi;
typedef long double ld;

ll mandelbrot(Complex c, ll max_iter)
{
    Complex z;
    ld it = 0;
    while (z.abs() <= 2 && it < max_iter)
    {
        z = z * z + c;
        it += 1;
    }
    return it; //==MAX_ITER ? it : it+1 - log(log2(z.abs()));
}
