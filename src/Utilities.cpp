#include <Utilities.hpp>
#include <Complex.hpp>
using namespace std;
typedef long long int ll;
typedef unsigned long int usi;
typedef long double ld;

Utilities::Utilities()
{
    re_start = RE_START;
    re_end = RE_END;
    im_start = IM_START;
    im_end = IM_END;
    max_iter = MAX_ITER;
    prev_max_iter = 0;
    zoom_numb = 0;
    running = true;
    t = new Tree(RESOL);
    reached_count = 0;
    count_protector = new counting_semaphore<1>(1);
    barrier = new counting_semaphore<THREAD_COUNT>(0);
    main_barrier = new counting_semaphore<1>(0);
}

Utilities::~Utilities()
{
    delete t;
    delete count_protector;
    delete barrier;
    delete main_barrier;
}

void colour_pixel(Utilities *u, sf::VertexArray *p, ld m)
{
    ld col_val = m == u->max_iter ? 1 : (m - ((ll)(m / MAX_ITER)) * MAX_ITER) / MAX_ITER;
    ll r = 0, g = 0, b = 0;
    if (col_val < 0.25)
    {
        r = 0 * (4 * col_val);
        g = 149 * (4 * col_val);
        b = 255 * (4 * col_val);
    }
    else if (col_val < 0.5)
    {
        r = 255 - 255 * (4 * (0.5 - col_val));
        g = 255 - 106 * (4 * (0.5 - col_val));
        b = 255 - 0 * (4 * (0.5 - col_val));
    }
    else if (col_val < 0.75)
    {
        r = 255 - 0 * (4 * (col_val - 0.5));
        g = 255 - 61 * (4 * (col_val - 0.5));
        b = 255 - 255 * (4 * (col_val - 0.5));
    }
    else if (col_val < 1)
    {
        r = 255 * (4 * (1 - col_val));
        g = 195 * (4 * (1 - col_val));
        b = 0 * (4 * (1 - col_val));
    }
    (*p)[0].color = sf::Color(r, g, b, 255);
    (*p)[1].color = sf::Color(r, g, b, 255);
    (*p)[2].color = sf::Color(r, g, b, 255);
    (*p)[3].color = sf::Color(r, g, b, 255);
}

void reset_pixel(Utilities *u, sf::VertexArray *pixel, ll x, ll y)
{
    Entry *e = u->t->get(u->zoom_numb, u->s.height(), x, y, RESOL);
    if (e->v == -1 || (e->v == u->prev_max_iter && u->prev_max_iter != u->max_iter))
    {
        // cout<<e->h;
        Complex c(u->re_start + ((ld)x / RESOL) * (u->re_end - u->re_start),
                  u->im_start + ((ld)y / RESOL) * (u->im_end - u->im_start));
        e->v = mandelbrot(c, u->max_iter);
    }
    // cout<<(*e);
    // if((y+1)%RESOL==0){
    //     cout<<"\n";
    // }
    // else{
    //     cout<<"\t";
    // }
    colour_pixel(u, pixel, e->v);
}

void init_pixel(Utilities *u, sf::VertexArray *pixel, ll x, ll y)
{
    (*pixel)[0].position = sf::Vector2f(x * PIXEL_WIDHT, y * PIXEL_HEIGHT);
    (*pixel)[1].position = sf::Vector2f(x * PIXEL_WIDHT, (y + 1) * PIXEL_HEIGHT);
    (*pixel)[2].position = sf::Vector2f((x + 1) * PIXEL_WIDHT, (y + 1) * PIXEL_HEIGHT);
    (*pixel)[3].position = sf::Vector2f((x + 1) * PIXEL_WIDHT, y * PIXEL_HEIGHT);
    reset_pixel(u, pixel, x, y);
}

void barrier_routine(Utilities *u)
{
    u->count_protector->acquire();
    u->reached_count++;
    cout << "\r"
         << "[";
    for (ll i = 0; i < THREAD_COUNT; i++)
    {
        if (i < u->reached_count)
            cout << "#";
        else
            cout << " ";
    }
    cout << "]" << flush;
    u->count_protector->release();

    if (u->reached_count == THREAD_COUNT)
    {
        u->reached_count = 0;
        u->main_barrier->release(1);
    }

    u->barrier->acquire();
}

void thread_routine(Utilities *u, sf::VertexArray ***pixels, ll x_start)
{
    for (ll x = x_start; x < x_start + THREAD_DIST; x++)
    {
        pixels[x] = new sf::VertexArray *[RESOL];
        for (ll y = 0; y < RESOL; y++)
        {
            pixels[x][y] = new sf::VertexArray(sf::Quads, 4);
            init_pixel(u, pixels[x][y], x, y);
        }
    }
    barrier_routine(u);
    while (u->running)
    {
        for (ll x = x_start; x < x_start + THREAD_DIST; x++)
        {
            for (ll y = 0; y < RESOL; y++)
            {
                reset_pixel(u, pixels[x][y], x, y);
            }
        }
        barrier_routine(u);
    }
}
