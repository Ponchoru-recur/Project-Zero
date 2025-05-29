#include "WindowRenderer.hpp"

Game game("2DGame!", 900, 700);

Game::Game(const char* name, int w, int h) : window_width(w), window_height(h) {
    if (w <= 0 || h <= 0) {
        std::cerr << "Invalid width or height\n";
        return;
    }
    SDL_SetAppMetadata("Tutel", "0.0.1", "com.cum.inside");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize VIDEO.\nError : %s", SDL_GetError());
        return;
    }
    if (!SDL_CreateWindowAndRenderer(name, w, h, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Failed to initialize Window or Renderer. \nError : %s", SDL_GetError());
        return;
    }
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

SDL_Window* Game::getWindow() {
    return window;
}

int Game::getWidth() {
    return window_width;
}

int Game::getHeight() {
    return window_height;
}
