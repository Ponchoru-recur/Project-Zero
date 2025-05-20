#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>

class GameObject {
    virtual void handleEvent(const SDL_Event &e);
    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer *renderer);
    virtual ~GameObject() = default;
};
