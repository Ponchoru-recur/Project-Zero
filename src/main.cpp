#define SDL_MAIN_USE_CALLBACKS 1

// Headers
#include "app.hpp"
#include "window.hpp"

// Libraries
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <memory>
#include <thread>
#include <chrono>

// LUA
extern "C" {
#include <luajit/lua.h>
#include <luajit/lauxlib.h>
#include <luajit/lualib.h>
}

#define FRAME_DELAY (1000 / 60)

SDL_AppResult SDL_AppInit(void **appstate, int /*argc*/, char * /*argv*/[]) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::unique_ptr<App>
        app = std::make_unique<App>();
    app->init();

    // release the raw pointer to appstate.
    // This is equivalent to *appstate = new App();
    *appstate = app.release();
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dostring(L, "print('Hello from LuaJIT!')");
    lua_close(L);

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

const float TargetFPS = 144.0f;
const float TargetFrameTIme = (1000.0f / TargetFPS);

SDL_AppResult SDL_AppIterate(void *appstate) {
    auto StartFrame = std::chrono::steady_clock::now();

    // Logic
    SDL_GL_MakeCurrent(window.getWindowMain(), window.getContextMain());
    glViewport(0, 0, window.getWidth(), window.getHeight());
    static_cast<App *>(appstate)->update();
    static_cast<App *>(appstate)->render();
    SDL_GL_SwapWindow(window.getWindowMain());

    // SDL_GL_MakeCurrent(window.getWindowDrawing(), window.getContextDrawing());
    // glViewport(0, 0, window.getWidth(), window.getHeight());
    // glClear(GL_COLOR_BUFFER_BIT);
    // glClearColor(1.0f, 0.5f, 0.2f, 1.0f);
    // SDL_GL_SwapWindow(window.getWindowDrawing());

    auto EndFrame = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(EndFrame - StartFrame);

    // Translate elapsed.count() to float to prevent error convertion.
    auto elapse = static_cast<float>(elapsed.count());
    if ((elapse) < TargetFrameTIme) {
        SDL_Delay(static_cast<std::uint32_t>(TargetFrameTIme - elapse));
    }

    // std::cout << "\rFPS: " << elapse * TargetFPS << "    " << std::flush;

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult /*result*/) {
    static_cast<App *>(appstate)->cleanup();
    delete static_cast<App *>(appstate);
    window.clean();
    std::cout << "Exited.\n";
}

// if you see this remember to try out bit manipulation and adding Luajit to you code
