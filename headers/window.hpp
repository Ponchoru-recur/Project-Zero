#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

class Window {
   public:
    // Example "Mario Window!" "600" "400"
    Window(const char* name, int w, int h);

    SDL_Window* getWindow();
    int getWidth();
    int getHeight();
    void clean();

   private:
    SDL_GLContext gl_context;
    SDL_Window* window;
    int window_width = 0;
    int window_height = 0;
};

extern Window window;
