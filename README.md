# Mastermind

**DEPENDENCIES**

* CMake
* Make
* GCC
* SDL-devel 1.2, SDL 1.2
* SDL_TTF-devel 1.2, SDL_TTF 1.2

**COMPILATION**

* "mkdir build"
* "cd build"
* "cmake .."
* "make"

Executables are available in "build/bin", program HAS TO be launched from build folder because of local access path to the font.

**KEYBOARD BUTTONS**

* "LEFT ARROW" / "RIGHT ARROW" move white cursor respectively on left or right
* "ENTER" selects the color targeted by the white cursor
* "BACKSPACE" removes the last color enter
* "ENTER" checks the given answer
* "ALT+F4" exits the game
  
**CLUES**

Clues given above each board column correspond to : "number of good positions : number of good colors"
