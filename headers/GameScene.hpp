#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <chrono>

#include "timer.hpp"
#include "WindowRenderer.hpp"

// Parent
class GameScene {
   public:
    GameScene() = default;
    virtual void handleEvent(const SDL_Event &e);
    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer *renderer);
    virtual ~GameScene() = default;

   protected:
};

class inGame : public GameScene {
   public:
    inGame() = default;
    void handleEvent(const SDL_Event &e) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer *renderer) override;
    ~inGame() = default;

   private:
};
