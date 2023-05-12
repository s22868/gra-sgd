//
// Created by Mateusz on 12.05.2023.
//

#ifndef GRASGD_SOUNDMANAGER_H
#define GRASGD_SOUNDMANAGER_H

#include <string>
#include <map>
#include "SDL_mixer.h"

class SoundManager {
public:
    static SoundManager *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new SoundManager();
    }

    bool Load(std::string id, std::string filename);

    void Clean();

    void Update();

    void PlaySound(std::string id, int loops = 0);

    void PlayMusic();
private:
    SoundManager() {
        volume = 10;
        Mix_VolumeMusic(6);
        Mix_Volume(-1, volume);
        music = Mix_LoadMUS("assets/sounds/bg.mp3");
        if(!music){
            SDL_Log("Nie udalo sie zaladowac muzyki, %s", Mix_GetError());
        }
    };
    int volume;
    std::map<std::string, Mix_Chunk *> soundMap;
    Mix_Music *music;
    static SoundManager *s_Instance;
};


#endif //GRASGD_SOUNDMANAGER_H
