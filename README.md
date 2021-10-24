# MandelbrotZoom

Goal is to create an interactive animation of zooming into the Mandelbrot set in C++

----

## Classes and Headers defined

- **ComplexNumber** - A class for complex numbers on the complex plane. Data type for real and imaginary components is taken as template argument for imporving precision later on. Supports operators such as +, -, *, /, !, ==, !=, [] and fucntions such as abs().
- ColourVector
- **MandelbrotMap** - A map that maps a given complex number on the complex plane, to a colour that it needs to be coloured with. Firstly the pixel is converted to complex number. This complex number is mapped to a integer using the [Optimised Escape-Time algorithm](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#:~:text=number%20of%20iterations.-,Optimized%20escape%20time%20algorithms,-%5Bedit%5D) which acts as the Hashing Function. Now the integer is compressed to a float between 0 to 1 using a simple compression map.
- Main
- Zooming
- Main with Multi-threading
- More precision

----

## CS-293 Project by Prof. Bhaskaran Raman

### Overall goals, principles

- Do substantial coding (~1500 lines or more), using data structures and algorithms learnt in the course.

- Write a design document first, before starting the implementation.

- Your code should be well commented, properly indented. Function and variable naming should be well done (don’t use context-free names like xyz, badlu1, etc).

- The code must be split across multiple files as necessary.  

> Implementation must be in simplecpp. If you want to use any other graphics package, talk to me first

1. There is this really interesting XScreenSaver of galaxies colliding with one another: <https://youtu.be/xBprAm9w-Fo> . Implement some version of this. You are free to design as you please, so long as the overall goals/principles above are achieved. You can include some interactivity to make it more interesting.`  

2. Learn about what the Mandelbrot set is. One of the most beautiful animations is that of Mandelbrot zoom. You can find tons of videos on this in YouTube. The math behind is simple yet captivating. Implement a Mandelbrot zoom. You can add in some interactivity if you like.

3. If there is anything else you want to do, talk to me first.

### Project grading

- Submission deadline will be roughly the end-sem date for CS213. Start working accordingly. Exact date to be decided after end-sem timetable is out.

- Submission and grading will be similar to CS101 project, if you did it. You will have to submit a short video showing your code+demo.

- Evaluation will be based on demo to two different TAs, each of whom will give you marks out of 50. Each TA will give a Yes/No. Instructor will resolve any discrepancies.

----
