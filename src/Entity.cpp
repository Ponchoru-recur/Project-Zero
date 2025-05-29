#include "Entity.hpp"

Animation::Animation(float _posy, float _posx) {
    std::cout << "Reached!\n";
    dest.x = 200;
    dest.y = 64;
    dest.w = dest.h = 64;
}

void Animation::addImage(const char* filepath, int frame_c_w, int frame_c_h) {
    SDL_Texture* texture = convertSurfaceToTexture(filepath);
    if (texture != nullptr) {
        t_frame_w = frame_c_w;
        t_frame_h = frame_c_h;
        SDL_GetTextureSize(texture, &t_w, &t_h);
        std::cout << "Image added!\n";
        images.push_back(texture);
        nextIndex++;
        return;
    }
    std::cout << "Error on ANIMATION addImage!\n";
}

void Animation::rowSlice(std::string name, int which_column_start, int which_column_end, int start_frame, int end_frame) {
    animations[name] = AnimationClip{name, which_column_start, which_column_end, start_frame, end_frame - 1, nextIndex, t_w, t_h, t_frame_w, t_frame_h};
}

void Animation::play(std::string name) {
    auto it = animations.find(name);
    if (it == animations.end()) {
        std::cout << "Invalid name to play!\n";
        return;
    }

    currentImgUsed = it->second.imageIndex;
    currentFramex = it->second.startFrame;
    currentFramey = currentColumn_start;
    endFrame = it->second.endFrame;
    startFrame = it->second.startFrame;
    img_width = it->second.img_width;
    img_height = it->second.img_height;
    frame_width_count = it->second.frame_count_w;
    frame_height_count = it->second.frame_count_h;
    currentColumn_start = it->second.column_start;
    currentColumn_stop = it->second.column_end;

    dest.w = img_width / frame_width_count;
    dest.h = img_height / frame_height_count;

    isPlaying = true;
}

void Animation::update(float deltaTime) {
    if (!isPlaying) {
        std::cout << "Retard\n";
        return;
    }

    float frameWidth = img_width / frame_width_count;

    if (timer::wait_till(duration)) {
        if ((currentFramex + 1) * frameWidth > img_width) {
            std::cout << "⚠️ Frame source out of bounds! currentFrame=" << currentFramex << "\n";
        }

        currentFramex++;
        if (currentFramex > endFrame) {
            currentFramex = startFrame;
            currentFramey++;
            if (currentFramey > currentColumn_stop) {
                currentFramey = currentColumn_start;
            }
        }
    }
}

void Animation::render() {
    if (!isPlaying) {
        std::cout << "Retard\n";
        return;
    }

    float frameWidth = img_width / frame_width_count;
    float frameHeight = img_height / frame_height_count;

    SDL_FRect src = {
        currentFramex * frameWidth,
        currentFramey * frameHeight,
        frameWidth,
        frameHeight};

    if (!images[currentImgUsed]) {
        std::cout << "Problem on image!\n";
        return;
    }

    // std::cout << "Start at : " << currentImgUsed << "\n";
    // SDL_SetRenderDrawColor(game.getRenderer(), 255, 0, 0, 255);
    // SDL_RenderFillRect(game.getRenderer(), &dest);  // red rectangle
    SDL_RenderTexture(game.getRenderer(), images[currentImgUsed], &src, &dest);
}

void Animation::modTiming(float milliseconds) {
    timer::modtimer(duration, milliseconds);
}

Animation::~Animation() {
    for (auto image : images) {
        SDL_DestroyTexture(image);
    }
    std::cout << "Animation cleaned!\n";
}
