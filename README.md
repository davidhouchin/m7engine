m7engine
========

A small 2D engine built with SDL2.

This was originally written in Allegro 5, but has been rewritten to completely utilize SDL libraries.
I am only working on this to teach myself programming. The code is more than likely abysmal, but
maybe somebody just starting out might pick something or two useful out of it.
My goal is for a somewhat workable engine that can compile for Windows, Linux, and eventually OSX.

Currently it supports and entity management system, keyboard/mouse input, simple collision detection,
simple sound playback, TTF rendering, INI-style read capability, vector maths, primitives drawing, some
timing utilities, and a simple resource manager, off the top of my head.

Building
========

I will expand this later on, and try to clean up and automate the build process.
I have successfully built it on Ubuntu 14.04, Windows 8.1, and OSX 10.9.
Currently the engine depends on SDL2, SDL2_image, SDL2_mixer, SDL2_ttf, and SDL2_gfx.
I also utilize C++11 features.



