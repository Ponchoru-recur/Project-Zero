#define SDL_MAIN_USE_CALLBACKS 1

// Libraries
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <memory>
#include <thread>
#include <chrono>

// Headers
#include "window.hpp"
#include "app.hpp"

#define w_window 900
#define h_window 700
#define FRAME_DELAY (1000 / 60)

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::unique_ptr<App> app = std::make_unique<App>();
    app->init();

    // release the raw pointer to appstate.
    // This is equivalent to *appstate = new App();
    *appstate = app.release();
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    SDL_PumpEvents();
    static_cast<App *>(appstate)->handleEvent(*event);
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_ESCAPE:
                    std::cout << "Bitch it works\n";
                    return SDL_APP_SUCCESS;
                case SDLK_N:
                    std::cout << "Banana\n";
                    return SDL_APP_CONTINUE;
                default:
                    break;
            }
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

const float TargetFPS = 60;
const float TargetFrameTIme = (1000.0f / TargetFPS);

SDL_AppResult SDL_AppIterate(void *appstate) {
    glViewport(0, 0, window.getWidth(), window.getHeight());
    auto StartFrame = std::chrono::steady_clock::now();

    // Logic
    static_cast<App *>(appstate)->update();

    // Start renderering below this
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);  // RGB blueish
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    static_cast<App *>(appstate)->render();
    SDL_GL_SwapWindow(window.getWindow());

    auto EndFrame = std::chrono::steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndFrame - StartFrame);

    if (elapsed.count() < TargetFrameTIme) {
        SDL_Delay((TargetFrameTIme - elapsed.count()));
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    static_cast<App *>(appstate)->cleanup();
    delete static_cast<App *>(appstate);
    window.clean();
    std::cout << "Exited.\n";
}
