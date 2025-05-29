#pragma once

#include <vector>
#include <unordered_map>
#include <SDL3/SDL.h>
#include "WindowRenderer.hpp"
#include "timer.hpp"

class Animation {
   public:
    Animation(float position_Y = 0, float position_X = 0);
    void addImage(const char* image_filepath, int frame_c_w, int frame_c_h);
    void rowSlice(std::string name, int column_frame_start, int column_frame_stop, int start_frame, int end_frame);

    void play(std::string play_name);
    void update(float deltaTime);
    void render();
    void modTiming(float Timing_milliseconds);
    ~Animation();

   protected:
    struct AnimationClip {
        std::string name;
        int column_start;
        int column_end;

        int startFrame;
        int endFrame;
        int imageIndex;
        float img_width;
        float img_height;
        int frame_count_w;
        int frame_count_h;
    };

    int duration = timer::create(800);

    int t_frame_w;
    int t_frame_h;
    float t_w = 0;
    float t_h = 0;

    int nextIndex = -1;
    // Using storage for whatever the fuck we're gonna play
    int currentImgUsed;
    int currentFramex;
    int currentFramey;
    int endFrame;
    int startFrame;
    float img_width;
    float img_height;
    int frame_width_count;
    int frame_height_count;
    int currentColumn_start;
    int currentColumn_stop;

    bool isPlaying = false;

    SDL_FRect dest;
    std::vector<SDL_Texture*> images;
    std::unordered_map<std::string, AnimationClip> animations;
};

class Entity : public Animation {
   public:
    Entity() = default;
    float x, y, w, h;
    virtual void update(float deltaTime);
    virtual void render();
    virtual ~Entity() = default;

   private:
    SDL_FRect body;
};
