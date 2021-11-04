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

void colour_pixel(sf::VertexArray* p,ld m){
    // m = (ll)(m/10) * 10;
    ld col_val = m / MAX_ITER;
    ll r=0,g=0,b=0;
    if(col_val<0.25){
        r = 0*(0.375+2.5*col_val);
        g = 149*(0.375+2.5*col_val);
        b = 255*(0.375+2.5*col_val);
    }
    else if(col_val<0.5){
        r = 255 - 255*(4*(0.5 - col_val));
        g = 255 - 106*(4*(0.5 - col_val));
        b = 255 - 0*(4*(0.5 - col_val));
    }
    else if(col_val<0.75){
        r = 255 - 0*(4*(col_val-0.5));
        g = 255 - 61*(4*(col_val-0.5));
        b = 255 - 255*(4*(col_val-0.5));
    }
    else if(col_val<1){
        r = 255*(0.25+3*(1 - col_val));
        g = 195*(0.25+3*(1 - col_val));
        b = 0*(0.25+3*(1 - col_val));
    }
    (*p)[0].color = sf::Color(r,g,b,255);
    (*p)[1].color = sf::Color(r,g,b,255);
    (*p)[2].color = sf::Color(r,g,b,255);
    (*p)[3].color = sf::Color(r,g,b,255);
}