#pragma once

#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <iostream>

class Window {
   public:
    // Example "Mario Window!" "600" "400"
    Window(const char* name, int w, int h);

    SDL_Window* getWindowMain();
    int getWidth();
    int getHeight();
    void clean();

    SDL_Window* getWindowDrawing();
    SDL_GLContext& getContextMain();
    SDL_GLContext& getContextDrawing();

   private:
    SDL_GLContext glContextMain;     // Main display for screen context
    SDL_GLContext glContextDrawing;  // Drawing display context
    SDL_Window* windowMainDisplay;
    SDL_Window* windowDrawingDisplay;
    int window_width = 0;
    int window_height = 0;
};

extern Window window;
