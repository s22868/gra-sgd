//
// Created by Mateusz on 03.05.2023.
//

#ifndef GRASGD_TEXTUREMANAGER_H
#define GRASGD_TEXTUREMANAGER_H

#include <string>
#include <map>
#include "SDL.h"

//singleton

class TextureManager {
public:
    static TextureManager *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
    }

    bool Load(std::string id, std::string filename);

    void Remove(std::string id);

    void Clean();

    void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawTile(std::string tilesetId, int tileSize, int x, int y, int row, int frame,
                  SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    TextureManager() {};
    std::map<std::string, SDL_Texture *> textureMap;
    static TextureManager *s_Instance;
};


#endif //GRASGD_TEXTUREMANAGER_H
