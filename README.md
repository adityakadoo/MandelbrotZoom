# MandelbrotZoom

## Author: Kadoo Aditya Anil (200050055)

### Goal: Create an interactive animation of zooming into the Mandelbrot set in C++ for the Project of the CS-293 course in Autumn 2021

----

## Despcription

Currently the app can create a window initialized to show the complete Mandelbrot Set on the complex plain. The user can click on one of the quadrants to zoom into it. Thus every time the user can zoom in 2x times. This can be done upto 20x times before the image get very blurry.

----

## Headers and Sources

- **Complex** - A class for implementing complex numbers on the complex plane. Data type for real and imaginary components is taken as template argument for flexibility. Supports operators such as +, -, *, /, !, ==, !=, [] and fucntions such as abs().

- **SFML** - External library used for rendering graphics and taking user input. It creates the window and takes mouse-clicks for zooming in.

### To be improved

- **Main** - Only a source file which has the actual main function that brings together all the headers to run the application. Currently only has zomming and is very slow. Plans to improve speed by adding multi-theading.

- **Mandelbrot** - Implements the functions related to the mandelbrot set. Currently contains 2 functions: mandelbrot() which executes the [Optimised Escape-Time algorithm](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#:~:text=number%20of%20iterations.-,Optimized%20escape%20time%20algorithms,-%5Bedit%5D) and colour_pixel() method to give colour to a certain pixel according to it's result from the mandelbrot() function.

### To be added

- A Map class to memoize the results from the Mandelbrot algorithm to imporve time complexity of the code using Data Stuctures

- A B-Tree class for internal storage of the MAP. This will give faster implementation.

- A class for dynamic floats to improve precision

- Tests to see if complexity is actually improving

----

## Problem Statement by Prof. Bhaskaran Raman

### Overall goals, principles

- Do substantial coding (~1500 lines or more), using data structures and algorithms learnt in the course.

- Write a design document first, before starting the implementation.

- Your code should be well commented, properly indented. Function and variable naming should be well done (don’t use context-free names like xyz, badlu1, etc).

- The code must be split across multiple files as necessary.  

Implementation must be in simplecpp. If you want to use any other graphics package, talk to me first

1. There is this really interesting XScreenSaver of galaxies colliding with one another: <https://youtu.be/xBprAm9w-Fo> . Implement some version of this. You are free to design as you please, so long as the overall goals/principles above are achieved. You can include some interactivity to make it more interesting.`  

2. Learn about what the Mandelbrot set is. One of the most beautiful animations is that of Mandelbrot zoom. You can find tons of videos on this in YouTube. The math behind is simple yet captivating. Implement a Mandelbrot zoom. You can add in some interactivity if you like.

3. If there is anything else you want to do, talk to me first.

### Project grading

- Submission deadline will be roughly the end-sem date for CS213. Start working accordingly. Exact date to be decided after end-sem timetable is out.

- Submission and grading will be similar to CS101 project, if you did it. You will have to submit a short video showing your code+demo.

- Evaluation will be based on demo to two different TAs, each of whom will give you marks out of 50. Each TA will give a Yes/No. Instructor will resolve any discrepancies.

----
