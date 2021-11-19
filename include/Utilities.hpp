#ifndef __UTILITIES__
#define __UTILITIES__
#include <SFML/Graphics.hpp>
#include <semaphore>
#include <chrono>
#include <Mandelbrot.hpp>
#include <Tree.hpp>
#include <Stack.hpp>
using namespace std;

/* Window settings */
#define WINDOW_WIDTH 1200.0
#define WINDOW_HEIGHT 800.0
#define RESOL 1024
#define PIXEL_WIDHT WINDOW_WIDTH / RESOL
#define PIXEL_HEIGHT WINDOW_HEIGHT / RESOL

/* MultiThreading settings */
#define THREAD_COUNT 16
#define THREAD_DIST RESOL / THREAD_COUNT

class Utilities
{
public:
    /* Timer variables */
    chrono::_V2::high_resolution_clock::time_point start;
    chrono::_V2::high_resolution_clock::time_point stop;
    chrono::microseconds duration;

    /* State variables */
    long double re_start;
    long double re_end;
    long double im_start;
    long double im_end;
    long long zoom_numb;
    long long max_iter;
    bool running;

    // Zooming stack
    Stack s;

    // Memoisation Tree
    Tree* t;

    /* Multithreading variables */
    // number of threads that reached the barrier
    long long reached_count;
    // Mutex for protecting reached_count
    counting_semaphore<1> *count_protector;
    // barrier for threads
    counting_semaphore<THREAD_COUNT> *barrier;
    // barrier for main thread
    counting_semaphore<1> *main_barrier;

    // Default Constructor
    Utilities();
    // Default Destructor
    ~Utilities();
};

/* Functions for Pixel Manipulation */
// Colours a pixel
void colour_pixel(Utilities *, sf::VertexArray *, long double);
// Resets a pixel
void reset_pixel(Utilities *, sf::VertexArray *, long long, long long);
// Initializes a pixel
void init_pixel(Utilities *, sf::VertexArray *, long long, long long);

/* Multithreading Functions */
// Implements a reusable barrier for threads
// to wait till every thread finishes execution
void barrier_routine(Utilities *);
// Defines the routine for a thread
void thread_routine(Utilities *, sf::VertexArray ***, long long);

#endif