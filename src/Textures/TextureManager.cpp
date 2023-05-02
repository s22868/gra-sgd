//
// Created by Mateusz on 02.05.2023.
//

#include "TextureManager.h"
#include "../Core/Engine.h"

bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface *surface = SDL_LoadBMP(filename.c_str());

    if (surface == nullptr) {
        SDL_Log("Nie udalo sie zaladowac pliku, %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);

    if (texture == nullptr) {
        SDL_Log("Nie udalo sie stworzyc tekstury z pliku, %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }
    textureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}


void TextureManager::Remove(std::string id) {

}

void TextureManager::Clean() {

}

