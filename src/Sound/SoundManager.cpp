//
// Created by Mateusz on 12.05.2023.
//

#include <SDL_log.h>
#include "SoundManager.h"
#include "../InputHandler/InputHandler.h"

SoundManager *SoundManager::s_Instance = nullptr;

bool SoundManager::Load(std::string id, std::string filename) {
    Mix_Chunk *sound;

    sound = Mix_LoadWAV(("assets/sounds/" + filename).c_str());

    if (!sound) {
        SDL_Log("Nie udalo sie zaladowac dzwieku, %s, %s", filename.c_str(), Mix_GetError());
        return false;
    }

    soundMap[id] = sound;
    return true;
}

void SoundManager::Clean() {
    Mix_FreeMusic(music);
    std::map<std::string, Mix_Chunk *>::iterator it;
    for (it = soundMap.begin(); it != soundMap.end(); it++) {
        Mix_FreeChunk(it->second);
    }
    soundMap.clear();
}


void SoundManager::PlaySound(std::string id, int loops) {
    Mix_PlayChannel(-1, soundMap[id], loops);
}

void SoundManager::PlayMusic() {
    int result = Mix_PlayMusic(music, -1);
    if (result != 0) {
        SDL_Log("Nie udalo sie odtworzyc muzyki: %s", Mix_GetError());
    }
}

void SoundManager::Update() {
    if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_KP_PLUS)) {
        if (volume >= MIX_MAX_VOLUME - 1) {
            return;
        }
        ++volume;
        Mix_VolumeMusic(volume);
    }
    if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_KP_MINUS)) {
        if (volume <= 0) {
            return;
        }
        --volume;
        Mix_VolumeMusic(volume);
    }
}
