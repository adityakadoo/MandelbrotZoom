#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <Complex.hpp>
#include <Mandelbrot.hpp>

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
typedef long long int ll;
typedef unsigned long int usi;
typedef long double ld;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Set");
    window.setKeyRepeatEnabled(false);
    ld re_start = RE_START;
    ld re_end = RE_END;
    ld im_start = IM_START;
    ld im_end = IM_END;
    
    sf::VertexArray* pixels[X_RESOL][Y_RESOL];
    for(ll x=0;x<X_RESOL;x++){
        for(ll y=0; y<Y_RESOL; y++)
        {
            pixels[x][y] = new sf::VertexArray(sf::Quads, 4);

            (*pixels[x][y])[0].position = sf::Vector2f(x*PIXEL_WIDHT, y*PIXEL_HEIGHT);
            (*pixels[x][y])[1].position = sf::Vector2f(x*PIXEL_WIDHT, (y+1)*PIXEL_HEIGHT);
            (*pixels[x][y])[2].position = sf::Vector2f((x+1)*PIXEL_WIDHT, (y+1)*PIXEL_HEIGHT);
            (*pixels[x][y])[3].position = sf::Vector2f((x+1)*PIXEL_WIDHT, y*PIXEL_HEIGHT);

            Complex<ld> c(re_start + ((ld)x / X_RESOL)*(re_end - re_start),
                            im_start + ((ld)y / Y_RESOL)*(im_end - im_start));
            ld m = mandelbrot(c);
            colour_pixel(pixels[x][y],m);
        }
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
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "mouse x: " << event.mouseButton.x << " ";
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    bool x_sec = event.mouseButton.x > WINDOW_WIDTH/2;
                    bool y_sec = event.mouseButton.y > WINDOW_HEIGHT/2;
                    if(x_sec && y_sec){
                        re_start = re_start + (re_end - re_start)/2;
                        im_start = im_start + (im_end - im_start)/2;
                    }
                    else if(x_sec){
                        re_start = re_start + (re_end - re_start)/2;
                        im_end = im_start + (im_end - im_start)/2;
                    }
                    else if(y_sec){
                        re_end = re_start + (re_end - re_start)/2;
                        im_start = im_start + (im_end - im_start)/2;
                    }
                    else{
                        re_end = re_start + (re_end - re_start)/2;
                        im_end = im_start + (im_end - im_start)/2;
                    }

                    for(ll x=0;x<X_RESOL;x++){
                        for(ll y=0;y<Y_RESOL;y++){
                            Complex<ld> c(re_start + ((ld)x / X_RESOL)*(re_end - re_start),
                                            im_start + ((ld)y / Y_RESOL)*(im_end - im_start));
                            ld m = mandelbrot(c);
                            colour_pixel(pixels[x][y],m);
                        }
                    }
                }
            }
        }
        window.clear();
        for(ll i=0;i<X_RESOL*Y_RESOL;i++){
            window.draw(*pixels[i/Y_RESOL][i%Y_RESOL]);
        }
        window.display();
    }

    return 0;
}