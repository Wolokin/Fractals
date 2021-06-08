# Fractals
## Description
This is a simple app made for generating, viewing and exploring various fractals. Currently base classes are implemented for escape-time fractals and newton fractals with a few predefined fractals:
- Burning ship fractal
- Mandelbrot set
- Tricorn fractal
- Three Julia sets
- Five Newton fractals
- One miscellaneous
## Prerequisites
To compile this program you need OpenGL Mesa libraries, especially:
```sh
sudo apt-get install libglu1-mesa-dev mesa-common-dev
```
as well as Qt5 (I've tested this on version 5.12.8). Here's a comprehensive installation guide: https://doc.qt.io/qt-5/gettingstarted.html
## Usage
You can change currently displayed fractal as well as the color palette with the drop-down lists on the left. Fractal exploration is mainly done using mouse:
- Zoom-in/Zoom-out with the scroll wheel or with LB/RB
- Center the fractal on the mouse with middle button
Some additional controls are:
- Increase/decrease maximum iterations during computations with '+' and '-'
- Increase/decrease minimum iterations during computations with '[' and ']'
- Change the calulation domain with arrows: pressing an arrow expands domain in that direction. Pressing an arrow with Control key down does the reverse.
## Adding new fractals
Adding new fractals with already implemented base class (currently these are escape-time and Newton fractals) is very simple. You just need to add a new entry in the fractal map in the fractalsSupplier.h file.
### Adding new escape-time fractal
This fractal is created using base class EscapeTimeFractal
```c++
            {
                    "Your escape-time fractal name",
                    new EscapeTimeFractal([](complex<double> zn, double x, double y) {
                        return yourFunction(zn, x, y); // Should return $z_{n+1}$
                    })
            },
```
### Adding new Newton fractal
This fractal is created using base class NewtonFractal
```c++
            {
                    "Your Newton fractal name",
                    new NewtonFractal([](complex<double> z) { return someComplexFunction(z); },
                                      [](complex<double> z) { return derivativeOfSomeComplexFunction(z); })
            },
```
