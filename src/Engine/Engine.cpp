//
// Created by Mateusz on 02.05.2023.
//

#include "Engine.h"
#include "../Textures/TextureManager.h"
#include "../Hero/Player.h"
#include "../InputHandler/InputHandler.h"
#include "../Time/Time.h"
#include "../Map/MapParser.h"
#include "../Hero/Camera.h"
#include "../Collecting/Score.h"
#include "../Collision/CollisionHandler.h"
#include "../Text/TextManager.h"


Engine *Engine::s_Instance = nullptr;
Player *player = nullptr;
Score *score = nullptr;
int currentLevel = 1;
int deaths = 0;

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Nie udalo sie zaladowac SDL, %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        SDL_Log("Nie udalo sie zaldować SDL_ttf, %s", TTF_GetError());
        return false;
    }


    window = SDL_CreateWindow("Gra SGD",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Nie udalo sie utworzyć okna, %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        SDL_Log("Nie udalo sie utworzyć renderera, %s", SDL_GetError());
        return false;
    }

    TextManager::GetInstance()->Load("level", "LEVEL:" + std::to_string(currentLevel), {0, 0, 0});
    TextManager::GetInstance()->Load("deaths", "DEATHS:" + std::to_string(deaths), {255, 111, 51});

    TextureManager::GetInstance()->Load("bg", "test.bmp");

    if (!MapParser::GetInstance()->Load()) {
        SDL_Log("Nie udalo sie zaladowac mapy");
    }

    level = MapParser::GetInstance()->GetMap("LEVEL-" + std::to_string(currentLevel));

    TextureManager::GetInstance()->Load("player_idle", "player-idle.bmp");
    TextureManager::GetInstance()->Load("player_run", "player-run.bmp");

    TextureManager::GetInstance()->Load("fish", "fish.bmp");
    //TODO: Jump animation

//    TextureManager::GetInstance()->Load("player_jump", "player-jump.bmp");

    player = new Player(new Props("player_idle", 20, 416, 64, 32));
    score = new Score(new Props("fish", 900, 450, 32, 32));


    Camera::GetInstance()->SetTarget(player->GetOrigin());

    return isRunning = true;
}

bool Engine::Clean() {
    TextureManager::GetInstance()->Clean();
    TextManager::GetInstance()->Clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return false;
}

bool Engine::Quit() {
    return isRunning = false;
}

void Engine::Update() {
    float dt = Time::GetInstance()->GetDeltaTime();
    //TODO: create update function or remove it
    level->Update();
    score->Update(dt);

    if (CollisionHandler::GetInstance()->CheckCollision(player->collider->Get(), score->collider->Get())) {
        NextLevel();
    }

    player->Update(dt);
    Camera::GetInstance()->Update(dt);

}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);
    SDL_RenderClear(renderer);

    TextureManager::GetInstance()->DrawBg("bg", 100, 100, 742, 349);

    TextManager::GetInstance()->Draw("level", 10, 10);
    TextManager::GetInstance()->Draw("deaths", 700, 10);

    score->Draw();

    level->Render();

    player->Draw();


    SDL_RenderPresent(renderer);
}

void Engine::Events() {
    InputHandler::GetInstance()->Listen();
}

void Engine::NextLevel() {
    currentLevel++;
    score->Next("LEVEL-" + std::to_string(currentLevel));
    player->transform->Set(20, 400);
    level = MapParser::GetInstance()->GetMap("LEVEL-" + std::to_string(currentLevel));
    TextManager::GetInstance()->Remove("level");
    TextManager::GetInstance()->Load("level", "LEVEL:" + std::to_string(currentLevel), {0, 0, 0});
    CollisionHandler::GetInstance()->UpdateMapCollision();
}

void Engine::RestartLevel() {
    deaths++;
    player->transform->Set(20, 400);
    TextManager::GetInstance()->Remove("deaths");
    TextManager::GetInstance()->Load("deaths", "DEATHS:" + std::to_string(deaths), {255, 111, 51});
}
