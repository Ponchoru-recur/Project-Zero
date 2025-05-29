#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

class Game {
   public:
    // Example "Mario Game!" "600" "400"
    Game(const char* name, int w, int h);
    void clean();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
    int getWidth();
    int getHeight();

   private:
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    int window_width = 0;
    int window_height = 0;
};

extern Game game;

// TODO: MAKE SOMETHING THAT YOU CAN CALL MORE THAN ONCE TO
// TO GENERATE AN SURFACE TO TEXTURE

inline SDL_Texture* convertSurfaceToTexture(const char* filepath) {
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;

    surface = IMG_Load(filepath);
    if (!surface) {
        SDL_Log("Something went wrong with the SURFACE %s\n", SDL_GetError());
        return nullptr;
    }
    texture = SDL_CreateTextureFromSurface(game.getRenderer(), surface);

    if (!texture) {
        SDL_Log("Something went wrong with the TEXTURE %s\n", SDL_GetError());
        return nullptr;
    }
    SDL_DestroySurface(surface);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    std::cout << "Filepath : " << filepath << "\n";
    return texture;
}
