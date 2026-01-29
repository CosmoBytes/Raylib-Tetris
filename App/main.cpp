//
// Project: Reylib Tetris
// Description: Tetris Game implemented in Reylib and C++ for learning purposes
// Source / Reference:
// https://www.youtube.com/watch?v=wVYKG_ch4yM&list=PLwR6ZGPvjVOSRywn9VCQ3yrRVruxzzuo9
//
// Author: Arcane Compiler
// Created: December 29th 2025
//
#include <iostream>
#include "Renderer/Window.hpp"
#include "appLayer.hpp"

auto main() -> int {
    Core::WindowSpecification m_WindowSpecification;
    m_WindowSpecification.Title = "Raylib Tetris";
    m_WindowSpecification.Height = 500;
    m_WindowSpecification.Width = 620;
    m_WindowSpecification.FrameRate = 60;
    m_WindowSpecification.ImageIcon = "Images/test.png";

    Core::Window window(m_WindowSpecification);
    Game game("Fonts/monogram.ttf", 64); 
    window.Create();
    window.Run(game);

    return EXIT_SUCCESS;
}