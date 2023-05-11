//
// Created by Mateusz on 11.05.2023.
//

#ifndef GRASGD_TEXTMANAGER_H
#define GRASGD_TEXTMANAGER_H

#include <string>
#include <map>
#include <SDL_ttf.h>
#include "SDL.h"

struct TextTexture {
    SDL_Texture *txt;
    int w;
    int h;
};

class TextManager {
public:
    static TextManager *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextManager();
    }

    bool Load(std::string id, std::string text, SDL_Color color);

    void Remove(std::string id);

    void Clean();

    void Draw(std::string id, int x, int y);

    void SetFontSize(int fontSize);

private:
    TextManager() {
        font = TTF_OpenFont("ps2p.ttf", 24);
        if (!font) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
        }
    };
    std::map<std::string, TextTexture> textMap;
    TTF_Font *font;
    static TextManager *s_Instance;
};


#endif //GRASGD_TEXTMANAGER_H
