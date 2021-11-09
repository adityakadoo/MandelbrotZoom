#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <semaphore>
#include <Complex.hpp>
#include <Mandelbrot.hpp>
#include <Utilities.hpp>
using namespace std;
typedef long long int ll;
typedef unsigned long int usi;
typedef long double ld;

int main(int argc, char const *argv[])
{
    Utilities *u = new Utilities;
    vector<std::thread *> threads(THREAD_COUNT);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Set");
    window.setKeyRepeatEnabled(false);
    sf::VertexArray **pixels[X_RESOL];

    u->start = chrono::high_resolution_clock::now();
    for (ll i = 0; i < THREAD_COUNT; i++)
    {
        threads[i] = new thread(thread_routine, u, pixels, i * THREAD_DIST);
    }
    u->main_barrier->acquire();
    u->stop = chrono::high_resolution_clock::now();
    u->duration = chrono::duration_cast<chrono::microseconds>(u->stop - u->start);
    cout << "\r" << (ld)u->duration.count() / 1000000 << " seconds taken\n";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                u->running = false;
                u->barrier->release(THREAD_COUNT);
                for (ll i = 0; i < THREAD_COUNT; i++)
                {
                    threads[i]->join();
                    delete threads[i];
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bool x_sec = event.mouseButton.x > WINDOW_WIDTH / 2;
                    bool y_sec = event.mouseButton.y > WINDOW_HEIGHT / 2;
                    if (x_sec && y_sec)
                    {
                        u->re_start = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_start = u->im_start + (u->im_end - u->im_start) / 2;
                    }
                    else if (x_sec)
                    {
                        u->re_start = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_end = u->im_start + (u->im_end - u->im_start) / 2;
                    }
                    else if (y_sec)
                    {
                        u->re_end = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_start = u->im_start + (u->im_end - u->im_start) / 2;
                    }
                    else
                    {
                        u->re_end = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_end = u->im_start + (u->im_end - u->im_start) / 2;
                    }

                    u->start = chrono::high_resolution_clock::now();
                    u->barrier->release(THREAD_COUNT);
                    u->main_barrier->acquire();
                    u->stop = chrono::high_resolution_clock::now();
                    u->duration = chrono::duration_cast<chrono::microseconds>(u->stop - u->start);
                    cout << "\r" << (ld)u->duration.count() / 1000000 << " seconds taken\n";
                }
            }
        }
        window.clear();
        for (ll i = 0; i < X_RESOL * Y_RESOL; i++)
        {
            window.draw(*pixels[i / Y_RESOL][i % Y_RESOL]);
        }
        window.display();
    }

    return 0;
}