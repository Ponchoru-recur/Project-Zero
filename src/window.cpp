#include "window.hpp"

Window window("Freak November", 1024, 1024);

Window::Window(const char* name, int w, int h) : window_width(w), window_height(h) {
    if (w <= 0 || h <= 0) {
        std::cerr << "Invalid width or height\n";
        return;
    }
    SDL_SetAppMetadata(name, "0.0.1", "com.cum.inside");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize VIDEO.\nError : %s", SDL_GetError());
        return;
    }

    // Setting opengl version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    // Will make life miserable if disabled.
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    windowMainDisplay = SDL_CreateWindow(name, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    // windowDrawingDisplay = SDL_CreateWindow("Drawing window", w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!windowMainDisplay /*|| !windowDrawingDisplay*/) {
        std::cerr << "window failed to init Error : " << SDL_GetError() << "\n";
        SDL_DestroyWindow(windowMainDisplay);
        // SDL_DestroyWindow(windowDrawingDisplay);
        return;
    }

    glContextMain = SDL_GL_CreateContext(windowMainDisplay);

    // glContextDrawing = SDL_GL_CreateContext(windowDrawingDisplay);

    if (!glContextMain /*|| !glContextDrawing*/) {
        std::cerr << "Failed to create SDL_GL_CONTEXT : " << SDL_GetError() << "\n";
        SDL_DestroyWindow(windowMainDisplay);
        // SDL_DestroyWindow(windowDrawingDisplay);
        SDL_Quit();
        return;
    }

    if (!gladLoaderLoadGL()) {
        std::cerr << "Failed to initialize GLAD\n";
        SDL_GL_DestroyContext(glContextMain);
        // SDL_GL_DestroyContext(glContextDrawing);
        SDL_DestroyWindow(windowMainDisplay);
        // SDL_DestroyWindow(windowDrawingDisplay);
        SDL_Quit();
        return;
    }

    if (!GLAD_GL_ARB_bindless_texture) {
        std::cerr << "Bindless texture not supported on this hardware." << std::endl;
        return;
    }
}

void Window::clean() {
    SDL_GL_DestroyContext(glContextMain);
    // SDL_GL_DestroyContext(glContextDrawing);
    SDL_DestroyWindow(windowMainDisplay);
    // SDL_DestroyWindow(windowDrawingDisplay);
    SDL_Quit();
}

SDL_Window* Window::getWindowMain() {
    return windowMainDisplay;
}

SDL_Window* Window::getWindowDrawing() {
    return windowDrawingDisplay;
}

SDL_GLContext& Window::getContextMain() {
    return glContextMain;
}

SDL_GLContext& Window::getContextDrawing() {
    return glContextDrawing;
}

int Window::getWidth() {
    return window_width;
}

int Window::getHeight() {
    return window_height;
}
