#ifndef __MANDELBROT__
#define __MANDELBROT__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <Complex.hpp>

// Mandelbrot settings
#define RE_START -2.0
#define RE_END 1.0
#define IM_START -1.0
#define IM_END 1.0
#define MAX_ITER 100

// Implements the mandelbrot escape-time algorithm
// Returns the 0-1 ratio of result to Max_iter
long double mandelbrot(Complex);

#endif