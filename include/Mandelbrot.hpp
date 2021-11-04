#ifndef __MANDELBROT__
#define __MANDELBROT__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <Complex.hpp>

#define MAX_ITER 500

// Implements the mandelbrot escape-time algorithm
long double mandelbrot(Complex);
// Gives color to a given pixel
void colour_pixel(sf::VertexArray*,long double);

#endif