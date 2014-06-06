m7engine
========

A small 2D engine built with Allegro 5.0. Currently only for self-educational purposes.

I originally wrote this in Linux using a number of libraries, including SDL and straight-up OpenGL,
but have mostly settled on Allegro 5. Getting back into programming, I found this and fixed it to compile
under MSVC 12. I intend to continue to work on this while going to school and eventually getting
somewhat of a workable engine that can compile for Windows, Linux, and eventually OSX.

Unfortunately I will have to reteach myself to program, and possibly rewrite a good portion of the source
to get it underway again. I may eventually choose a new game library as well, but have yet to decide.
Either way, I do plan on expanding this.

Current (somewhat) features include:
-An entity based system
-Input manager for keyboard/mouse
-Simple collision manager
-Simple sound manager
-Particle emitter
-Font rendering (Currently broken on Windows)
-Primitive drawing capabilities
-And vector maths

My hope is to clean it up quite a bit more and add/fix some more of the following..
-Display depth for entities
-Sound revamp
-Bitmap fonts
-Particle system revamp (Is pretty fudgy currently)
-Some more timing utilites
-Lower level graphics (bitmaps, backgrounds, etc)
-Resource manager
-Fix font rendering under Windows (Nice to see the debug info, if anything)
-Crashes while exiting (Has to do with Allegro destructors)

