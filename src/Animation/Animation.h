//
// Created by Mateusz on 03.05.2023.
//

#ifndef GRASGD_ANIMATION_H
#define GRASGD_ANIMATION_H


#include <string>
#include <SDL.h>

class Animation {
public:
    Animation() {};

    void Update();

    void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void SetProps(std::string textureIdParam, int spriteRowParam, int frameCountParam, int animationSpeedParam);

private:
    int spriteRow, spriteFrame, animationSpeed, frameCount;
    std::string textureId;
};


#endif //GRASGD_ANIMATION_H
