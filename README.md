m7engine
========

A small 2D engine built with SDL2.

This was originally written in Allegro 5, but has been rewritten to completely utilize SDL libraries.
I am only working on this to teach myself programming. The code is more than likely abysmal for now, but
maybe somebody just starting out might pick something or two useful out of it.
My goal is for a somewhat workable engine that can compile for Windows, Linux, and OSX.

Currently it supports an entity management system, keyboard/mouse input, simple collision detection,
simple sound playback, TTF rendering, INI-style read capability, vector maths, primitives drawing, some
timing utilities, and a very simple resource manager, off the top of my head.

Building
========

I will expand this later on, and try to clean up and automate the build process.

The project requires SDL2, SDL2_Mixer, SDL2_Image, and SDL2_TTF.
It should build as-is with cmake under Linux if you have the prerequisites installed.

$ mkdir build && cd build
$ cmake ..
$ make

Under Visual Studio, it should build using the defaults as long as you add the SDL libraries.
Compiling with debug flags is far too slow right now, so do release.
Also, distributing this will require the msvcp and msvcr libraries associated with the Visual C++ version.
