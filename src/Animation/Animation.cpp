//
// Created by Mateusz on 03.05.2023.
//

#include "Animation.h"
#include "../Textures/TextureManager.h"

void Animation::Update() {
    spriteFrame = (SDL_GetTicks() / animationSpeed) % frameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip) {
    TextureManager::GetInstance()->DrawFrame(textureId, x, y, spriteWidth, spriteHeight, spriteRow, spriteFrame, flip);
}

void
Animation::SetProps(std::string textureIdParam, int spriteRowParam, int frameCountParam, int animationSpeedParam) {
    textureId = textureIdParam;
    spriteRow = spriteRowParam;
    frameCount = frameCountParam;
    animationSpeed = animationSpeedParam;
}
