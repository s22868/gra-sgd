//
// Created by Mateusz on 02.05.2023.
//

#ifndef GRASGD_ENGINE_H
#define GRASGD_ENGINE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "../Map/GameMap.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

//singleton
class Engine {
public:
    static Engine *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }
    bool Init();
    bool Clean();
    bool Quit();

    void Update();
    void Render();
    void Events();

    inline GameMap* GetMap(){
        return level;
    }
    inline bool IsRunning(){
        return isRunning;
    };
    inline SDL_Renderer* GetRenderer(){
        return renderer;
    }


private:
    Engine(){};
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameMap* level;

    static Engine *s_Instance;
};


#endif //GRASGD_ENGINE_H
