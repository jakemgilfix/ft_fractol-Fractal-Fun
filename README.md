# Fract'ol : A 42 Silicon Valley Fractal Renderer

![screenshot](/screenshots/mandelbrot.png?raw=true)

A multi-threaded fractal renderer that supports six different (pre-defined) types of fractals.

This is the second project in the graphics branch of the old (pre-2020) curriculum at 42 Silicon Valley. It's built using the `minilibx` C library, which provides very basic graphics functions, like opening a window and drawing a pixel in that window. View the assignment [here](https://github.com/jakemgilfix/ft_fractol-Fractal-Fun/blob/master/fract_ol.en.pdf).

As with all 42 Silicon Valley projects, all code must comply with [42's style guide or 'Norme'](https://github.com/jakemgilfix/ft_fractol-Fractal-Fun/blob/master/norme.en.pdf). I would be remiss not to mention that this style guide is extremely dated and forces arbitrary constraints (e.g., 25 lines per function, 5 functions per file) that, however well-intended, often result in sub-optimal code.

## Features (required for project)
* Only C Standard Library functions allowed are: `open()`, `read()`, `write()`, `close()`, `malloc()`, `free()`, `perror()`, `strerror()`, `exit()`, and all of the functions within the `math` library.
* Includes Mandelbrot, Julia, and Tricorn fractals.
* Parameter of the Julia family of fractals is controllable via the mouse (without clicking).
* Mousewheel zooms in and out.
* Multicolored to show depth of fractals.

## Bonus Features (implemented for extra credit)
* Also includes Burning Ship fractal, as well as two different modified Julia fractals.
* Arrow keys to translate fractal up/down/left/right.
* `+`/`-` keys adjust maximum iterations.
* Zoom follows the mouse.

## Compiling and Running
Currently only tested on MacOS 10.13+.

Run `make` in the root directory to compile the project, leaving an executable which will be named `fractol`.

After compiling, run `./fractol` without arguments to display a list of the available fractal types and the keybindings you can use while running the program:
![screenshot](/screenshots/menu.png?raw=true)

To view a fractal from this list, run `./fractol <fractal_type>`, using the *name* and not the *number* (e.g., `./fractol Mandelbrot`).
