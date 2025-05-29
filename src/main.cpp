#define SDL_MAIN_USE_CALLBACKS 1

// Libraries
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_main.h>
#include <memory>

// Header files
#include "WindowRenderer.hpp"
#include "GameScene.hpp"
#include "Entity.hpp"

#define w_window 900
#define h_window 700
#define FRAME_DELAY (1000 / 60)

Animation player;

// Checks Elapsed time between frames
Uint64 last = 0;
float deltaTime = 0.0f;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    last = SDL_GetPerformanceCounter();

    player.addImage("../assets/images/wuh.png", 7, 1);
    player.rowSlice("walk", 0, 0, 0, 7);

    player.addImage("../assets/images/attack.png", 22, 1);
    player.rowSlice("attack", 0, 0, 0, 22);
    player.play("walk");

    player.addImage("../assets/images/FreePack.png", 5, 3);
    player.rowSlice("Testing", 0, 3, 0, 5);
    player.rowSlice("Testing2", 1, 1, 0, 5);

    player.modTiming(100);

    player.play("Testing2");

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_ESCAPE:
                    std::cout << "Bitch it works\n";
                    return SDL_APP_SUCCESS;
                default:
                    break;
            }
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    Uint64 now = SDL_GetPerformanceCounter();
    deltaTime = (float)(now - last) / SDL_GetPerformanceFrequency();
    last = now;

    // Logic for game
    player.update(deltaTime);

    SDL_SetRenderDrawColor(game.getRenderer(), 255, 100, 100, 255);
    SDL_RenderClear(game.getRenderer());
    // START RENDER HERE

    player.render();

    SDL_RenderPresent(game.getRenderer());

    float deltaMS = deltaTime * 1000;
    if (deltaMS < FRAME_DELAY) {
        SDL_Delay((Uint64)FRAME_DELAY - deltaMS);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    game.clean();
    std::cout << "Exited.\n";
}
