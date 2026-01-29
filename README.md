# Raylib-Tetris
Creation of Raylib Tetris implementation from a Youtube Tutorial. This project was based off of the work done here: https://www.youtube.com/watch?v=wVYKG_ch4yM&amp;list=PLwR6ZGPvjVOSRywn9VCQ3yrRVruxzzuo9

# Architecture

An example of architect applications in C++, as part of a [YouTube mini-series](https://youtube.com/playlist?list=PLlrATfBNZ98cpX2LuxLnLyLEmfD2FPpRA). 
Loosely based off of the series mentioned

<p align="center">
  <img src="https://github.com/CosmoBytes/Raylib-Tetris/blob/main/Raylib%20Tetris.png" width="200" height="400" alt="Raylib Tetris">
</p>

## Build

This project was built in Windows and can be built with the activate.ps1 script.
Generate project files/build using CMake. I like to make a directory called `build` at the root and then run. This also uses Ninja build 
if any dependencies are missing.
```
\activate.ps1 
```
from that directory. This will generate relevant project files (eg. Visual Studio Code for me) which you can then use to build and run.

## Notes
I chose to use Raylib which runs off of OpenGL (and GLFW) for this due following along in the tutorial mentioned in the description.

## License
This repository uses [MIT License](https://github.com/CosmoBytes/Raylib-Tetris/blob/main/LICENSE), so feel free to use this however you like.

// Project: Reylib Tetris
// Description: Tetris Game implemented in Reylib and C++ for learning purposes
// Source / Reference:
// https://www.youtube.com/watch?v=wVYKG_ch4yM&list=PLwR6ZGPvjVOSRywn9VCQ3yrRVruxzzuo9
//
// Author: Arcane Compiler
// Created: December 29th 2025
//
