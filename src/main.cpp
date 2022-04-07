#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <fstream>
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
    ofstream fout(argv[1]);

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mandelbrot Set");
    window->setKeyRepeatEnabled(false);
    sf::VertexArray **pixels[RESOL];

    u->start = chrono::high_resolution_clock::now();
    for (ll i = 0; i < THREAD_COUNT; i++)
    {
        threads[i] = new thread(thread_routine, u, pixels, i * THREAD_DIST);
    }
    u->main_barrier->acquire();
    u->stop = chrono::high_resolution_clock::now();
    u->duration = chrono::duration_cast<chrono::microseconds>(u->stop - u->start);
    cout << "\r" << (ld)u->duration.count() / 1000000 << " seconds taken\n";
    fout << (ld)u->duration.count() / 1000000 << flush << "\n";

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                u->running = false;
                u->barrier->release(THREAD_COUNT);
                for (ll i = 0; i < THREAD_COUNT; i++)
                {
                    threads[i]->join();
                    delete threads[i];
                }
                cout << "\r" << flush;
                continue;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bool x_sec = event.mouseButton.x > WINDOW_WIDTH / 2;
                    bool y_sec = event.mouseButton.y > WINDOW_HEIGHT / 2;
                    if (x_sec && y_sec)
                    {
                        u->zoom_numb += 3 * pow(FACTOR * FACTOR, u->s.height());
                        u->s.push(3);
                        u->t->zoom_in(u->zoom_numb, u->s.height(), RESOL, 3);
                        u->re_start = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_start = u->im_start + (u->im_end - u->im_start) / 2;
                    }
                    else if (x_sec)
                    {
                        u->zoom_numb += 2 * pow(FACTOR * FACTOR, u->s.height());
                        u->s.push(2);
                        u->t->zoom_in(u->zoom_numb, u->s.height(), RESOL, 2);
                        u->re_start = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_end = u->im_start + (u->im_end - u->im_start) / 2;
                    }
                    else if (y_sec)
                    {
                        u->zoom_numb += pow(FACTOR * FACTOR, u->s.height());
                        u->s.push(1);
                        u->t->zoom_in(u->zoom_numb, u->s.height(), RESOL, 1);
                        u->re_end = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_start = u->im_start + (u->im_end - u->im_start) / 2;
                    }
                    else
                    {
                        u->s.push(0);
                        u->t->zoom_in(u->zoom_numb, u->s.height(), RESOL, 0);
                        u->re_end = u->re_start + (u->re_end - u->re_start) / 2;
                        u->im_end = u->im_start + (u->im_end - u->im_start) / 2;
                    }
                    u->prev_max_iter = u->max_iter;
                    u->max_iter *= ITER_INC;
                    u->start = chrono::high_resolution_clock::now();
                    u->barrier->release(THREAD_COUNT);
                    u->main_barrier->acquire();
                    u->stop = chrono::high_resolution_clock::now();
                    u->duration = chrono::duration_cast<chrono::microseconds>(u->stop - u->start);
                    cout << "\r" << (ld)u->duration.count() / 1000000 << " seconds taken\n";
                    fout << (ld)u->duration.count() / 1000000 << flush << "\n";
                }
                else if (event.mouseButton.button == sf::Mouse::Right && !u->s.empty())
                {
                    u->zoom_numb %= (ll)pow(FACTOR * FACTOR, u->s.height() - 1);
                    switch (u->s.top())
                    {
                    case 0:
                        u->t->zoom_out(u->zoom_numb, u->s.height() - 1, RESOL, 0);
                        u->re_end = u->re_start + (u->re_end - u->re_start) * 2;
                        u->im_end = u->im_start + (u->im_end - u->im_start) * 2;
                        break;
                    case 1:
                        u->t->zoom_out(u->zoom_numb, u->s.height() - 1, RESOL, 1);
                        u->re_end = u->re_start + (u->re_end - u->re_start) * 2;
                        u->im_start = u->im_start - (u->im_end - u->im_start);
                        break;
                    case 2:
                        u->t->zoom_out(u->zoom_numb, u->s.height() - 1, RESOL, 2);
                        u->re_start = u->re_start - (u->re_end - u->re_start);
                        u->im_end = u->im_start + (u->im_end - u->im_start) * 2;
                        break;
                    case 3:
                        u->t->zoom_out(u->zoom_numb, u->s.height() - 1, RESOL, 3);
                        u->re_start = u->re_start - (u->re_end - u->re_start);
                        u->im_start = u->im_start - (u->im_end - u->im_start);
                        break;
                    default:
                        break;
                    }
                    u->s.pop();
                    u->prev_max_iter = u->max_iter;
                    u->max_iter /= ITER_INC;

                    u->start = chrono::high_resolution_clock::now();
                    u->barrier->release(THREAD_COUNT);
                    u->main_barrier->acquire();
                    u->stop = chrono::high_resolution_clock::now();
                    u->duration = chrono::duration_cast<chrono::microseconds>(u->stop - u->start);
                    cout << "\r" << (ld)u->duration.count() / 1000000 << " seconds taken\n";
                    fout << (ld)u->duration.count() / 1000000 << flush << "\n";
                }
            }
        }
        window->clear();
        for (ll i = 0; i < RESOL * RESOL; i++)
        {
            window->draw(*pixels[i / RESOL][i % RESOL]);
        }
        window->display();
        sf::Vector2i localPosition = window->getPosition();
        sf::Vector2i globalPosition = sf::Mouse::getPosition();
        ld x_coord = globalPosition.x - localPosition.x;
        ld y_coord = globalPosition.y - localPosition.y - 40;
        if (0 <= x_coord && x_coord <= WINDOW_WIDTH && 0 <= y_coord && y_coord <= WINDOW_HEIGHT)
        {
            Complex temp(u->re_start + (x_coord / WINDOW_WIDTH) * (u->re_end - u->re_start),
                         u->im_end - (y_coord / WINDOW_HEIGHT) * (u->im_end - u->im_start));
            cout << "\r" << temp << "  " << flush;
        }
    }

    return 0;
}