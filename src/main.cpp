#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_FRect walls[2];
SDL_FRect ball;

#define w_window 600
#define h_window 600
#define FRAME_DELAY (1000 / 60)

Uint64 last = 0;
float deltaTime = 0.0f;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Banana", "1.0", "com.cum");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize VIDEO.\nError : %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Mario", w_window, h_window, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Failed to initialize Window or Renderer. \nError : %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // Wall left
    walls[0].x = 100;
    walls[0].y = 100;

    walls[0].w = 10;
    walls[0].h = 40;

    // Wall right
    walls[1].x = 400;
    walls[1].y = 400;

    walls[1].w = 10;
    walls[1].h = 40;

    // Ball
    ball.x = 300;
    ball.y = 300;
    ball.w = 10;
    ball.h = 10;

    last = SDL_GetPerformanceCounter();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_KEY_DOWN:

            break;
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}
float ball_direction = -1;
bool collided = false;

float x, y = 0;

SDL_AppResult SDL_AppIterate(void *appstate) {
    const bool *keystates = SDL_GetKeyboardState(NULL);

    SDL_PumpEvents();
    Uint64 now = SDL_GetPerformanceCounter();
    float deltaTime = (float)(now - last) / SDL_GetPerformanceFrequency();
    last = now;

    SDL_GetMouseState(&x, &y);

    float speed = 100.0f;
    if (keystates[SDL_SCANCODE_W]) {
        walls[0].y += -speed * deltaTime;
    } else if (keystates[SDL_SCANCODE_S]) {
        walls[0].y += speed * deltaTime;
    }

    if (keystates[SDL_SCANCODE_UP]) {
        walls[1].y += -speed * deltaTime;
    } else if (keystates[SDL_SCANCODE_DOWN]) {
        walls[1].y += speed * deltaTime;
    }

    // Ball logic
    // float ball_speed = 100.0f * deltaTime;

    // if ((ball.x + ball.w) >= w_window || (ball.x) < 0) {
    //     ball.x = w_window / 2;
    // }
    // ball.x += (ball_speed * ball_direction);

    // for (SDL_FRect &wall : walls) {
    //     if (wall.x + wall.w >= ball.x) {
    //         std::cout << "Passed\n";
    //         ball_direction = -1;
    //         break;
    //     }
    // }

    ball.x = x;
    ball.y = y;
    // This took me an embarassing amount of time
    if ((walls[0].x + walls[0].w >= ball.x &&
         walls[0].y <= ball.y + ball.h &&
         walls[0].y + walls[0].h >= ball.y &&
         walls[0].x <= ball.x + ball.w)) {
        std::cout << "Passed\n";
        // ball_direction *= -1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
    SDL_RenderClear(renderer);

    // Walls
    SDL_SetRenderDrawColor(renderer, 10, 250, 255, 255);
    SDL_RenderFillRects(renderer, walls, 2);

    // Ball
    SDL_SetRenderDrawColor(renderer, 10, 10, 255, 255);
    SDL_RenderFillRect(renderer, &ball);

    SDL_RenderPresent(renderer);

    float deltaMS = deltaTime * 1000;
    if (deltaMS < FRAME_DELAY) {
        SDL_Delay((Uint64)FRAME_DELAY - deltaMS);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    std::cout << "Exited.\n";
}
