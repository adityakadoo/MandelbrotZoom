#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include "./Complex/Complex.hpp"
#include "./Map/Map.hpp"

#define MAX_ITER 200
#define WINDOW_WIDTH 1200.0
#define WINDOW_HEIGHT 800.0
#define X_RESOL 1200
#define Y_RESOL 800
#define PIXEL_WIDHT WINDOW_WIDTH/X_RESOL
#define PIXEL_HEIGHT WINDOW_HEIGHT/Y_RESOL
#define RE_START -2.0
#define RE_END 1.0
#define IM_START -1.0
#define IM_END 1.0
typedef unsigned long int ll;
typedef double ld;

void hsv2rgb(ld in_h,ld in_v,ld in_s,ld &out_r,ld &out_g,ld &out_b)
{
    // cout<<in_h<<" "<<in_v<<" "<<in_s<<"\n";
    double hh, p, q, t, ff;
    long i;

    if(in_s <= 0.0) {       // < is bogus, just shuts up warnings
        out_r = in_v;
        out_g = in_v;
        out_b = in_v;
        return;
    }
    hh = in_h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in_v * (1.0 - in_s);
    q = in_v * (1.0 - (in_s * ff));
    t = in_v * (1.0 - (in_s * (1.0 - ff)));

    switch(i) {
    case 0:
        out_r = in_v;
        out_g = t;
        out_b = p;
        break;
    case 1:
        out_r = q;
        out_g = in_v;
        out_b = p;
        break;
    case 2:
        out_r = p;
        out_g = in_v;
        out_b = t;
        break;

    case 3:
        out_r = p;
        out_g = q;
        out_b = in_v;
        break;
    case 4:
        out_r = t;
        out_g = p;
        out_b = in_v;
        break;
    case 5:
    default:
        out_r = in_v;
        out_g = p;
        out_b = q;
        break;
    }
    return;
}
   

ld mandelbrot(Complex<ld> c){
    Complex<ld> z;
    ld it = 0;
    while(z.abs()<=2 && it<MAX_ITER){
        z = z*z + c;
        it += 1;
        // cout<<it<<"\t"<<c<<"\t"<<z<<"\t"<<z.abs()<<"\n";
    }
    return it==MAX_ITER ? it : it+1 - log(log2(z.abs()));
}

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Set");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Magenta);
    // // create a quad
    // sf::VertexArray quad(sf::Quads, 4);

    // define it as a rectangle, located at (10, 10) and with size 100x100
    // quad[0].position = sf::Vector2f(10.f, 10.f);
    // quad[1].position = sf::Vector2f(11.f, 10.f);
    // quad[2].position = sf::Vector2f(11.f, 11.f);
    // quad[3].position = sf::Vector2f(10.f, 11.f);

    // // define its texture area to be a 25x50 rectangle starting at (0, 0)
    // quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    // quad[1].texCoords = sf::Vector2f(25.f, 0.f);
    // quad[2].texCoords = sf::Vector2f(25.f, 50.f);
    // quad[3].texCoords = sf::Vector2f(0.f, 50.f);

    sf::VertexArray* pixels[X_RESOL*Y_RESOL];
    for(ll i=0;i<X_RESOL*Y_RESOL;i++){
        pixels[i] = new sf::VertexArray(sf::Quads, 4);
        ll x = i/Y_RESOL;
        ll y = i%X_RESOL;

        // define it as a rectangle, located at (10, 10) and with size 100x100
        (*pixels[i])[0].position = sf::Vector2f(x*PIXEL_WIDHT, y*PIXEL_HEIGHT);
        (*pixels[i])[1].position = sf::Vector2f((x+1)*PIXEL_WIDHT, y*PIXEL_HEIGHT);
        (*pixels[i])[3].position = sf::Vector2f(x*PIXEL_WIDHT, (y+1)*PIXEL_HEIGHT);
        (*pixels[i])[2].position = sf::Vector2f((x+1)*PIXEL_WIDHT, (y+1)*PIXEL_HEIGHT);

        Complex<ld> c(RE_START + ((ld)x / X_RESOL)*(RE_END - RE_START),
                        IM_START + ((ld)y / Y_RESOL)*(IM_END - IM_START));
        // cout<<c<<" - ";
        ld m = mandelbrot(c);
        // cout<<m<<"\n";
        ll hue = (200 + ll(255 * (ld)m / MAX_ITER))%255;
        ll val = m<MAX_ITER ? 255 : 0;
        ll sat = 255;
        ld r,g,b;
        hsv2rgb((ld)hue/256,(ld)val/256,(ld)sat/256,r,g,b);

        (*pixels[i])[0].color = sf::Color(r*256,g*256,b*256,sat);
        (*pixels[i])[1].color = sf::Color(r*256,g*256,b*256,sat);
        (*pixels[i])[2].color = sf::Color(r*256,g*256,b*256,sat);
        (*pixels[i])[3].color = sf::Color(r*256,g*256,b*256,sat);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        // window.draw(shape);
        for(ll i=0;i<X_RESOL*Y_RESOL;i++){
            window.draw(*pixels[i]);
            // delete pixels[i];
        }
        window.display();
    }

    return 0;
}