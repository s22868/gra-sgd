//
// Created by Mateusz on 02.05.2023.
//

#include "Engine.h"

Engine *Engine::s_Instance = nullptr;

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Nie udalo sie zaladowac SDL, %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Gra SGD",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if(window == nullptr){
        SDL_Log("Nie udalo sie utworzyć okna, %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == nullptr) {
        SDL_Log("Nie udalo sie utworzyć renderera, %s", SDL_GetError());
        return false;
    }

    return isRunning = true;
}

bool Engine::Clean() {
    return false;
}

bool Engine::Quit() {
    return isRunning = false;
}

void Engine::Update() {
    SDL_Log("Dddd");
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Engine::Events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            Quit();
            break;
    }
}
