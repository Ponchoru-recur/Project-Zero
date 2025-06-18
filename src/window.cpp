#include "window.hpp"

Window window("2DWindow!", 1024, 1024);

Window::Window(const char* name, int w, int h) : window_width(w), window_height(h) {
    if (w <= 0 || h <= 0) {
        std::cerr << "Invalid width or height\n";
        return;
    }
    SDL_SetAppMetadata("Tutel", "0.0.1", "com.cum.inside");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize VIDEO.\nError : %s", SDL_GetError());
        return;
    }
    // Setting opengl version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("Opengl + SDL3", w, h, SDL_WINDOW_OPENGL);

    if (!window) {
        std::cerr << "window failed to init Error : " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        return;
    }

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "Failed to create SDL_GL_CONTEXT : " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        SDL_GL_DestroyContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

void Window::clean() {
    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* Window::getWindow() {
    return window;
}

int Window::getWidth() {
    return window_width;
}

int Window::getHeight() {
    return window_height;
}
