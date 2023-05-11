//
// Created by Mateusz on 11.05.2023.
//

#include "TextManager.h"
#include "../Engine/Engine.h"

TextManager *TextManager::s_Instance = nullptr;


bool TextManager::Load(std::string id, std::string text, SDL_Color color) {
    SDL_Surface *textSurface;

    textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        SDL_Log("Nie udalo sie wyrenderowac tekstu: %s", TTF_GetError());
        return false;
    }

    SDL_Texture *textTexture;

    textTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), textSurface);

    if (textTexture == nullptr) {
        SDL_Log("Nie udalo sie stworzyc tekstury z tekstu, %s", TTF_GetError());
        return false;
    }


    textMap[id].txt = textTexture;
    textMap[id].w = textSurface->w;
    textMap[id].h = textSurface->h;
    return true;

}
void TextManager::Draw(std::string id, int x, int y) {
    SDL_Rect dest = {0, 0, textMap[id].w, textMap[id].h};
    SDL_Rect src = {x, y, textMap[id].w, textMap[id].h};

    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), textMap[id].txt, &dest, &src);

}

void TextManager::SetFontSize(int fontSize) {
    TTF_SetFontSize(font, fontSize);
}

void TextManager::Remove(std::string id) {
    SDL_DestroyTexture(textMap[id].txt);
}


void TextManager::Clean() {
    std::map<std::string, TextTexture>::iterator it;
    for (it = textMap.begin(); it != textMap.end(); it++) {
        SDL_DestroyTexture(it->second.txt);
    }
    textMap.clear();
}


