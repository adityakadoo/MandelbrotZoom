#include <Mandelbrot.hpp>
typedef long long int ll;
typedef unsigned long int usi;
typedef long double ld;

ld mandelbrot(Complex c){
    Complex z;
    ld it = 0;
    while(z.abs()<=2 && it<MAX_ITER){
        z = z*z + c;
        it += 1;
        // cout<<it<<"\t"<<c<<"\t"<<z<<"\t"<<z.abs()<<"\n";
    }
    return it;//==MAX_ITER ? it : it+1 - log(log2(z.abs()));
}
