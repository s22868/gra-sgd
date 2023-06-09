//
// Created by Mateusz on 02.05.2023.
//

#include <SDL_mixer.h>
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
#include "../Sound/SoundManager.h"


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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        SDL_Log("Error initializing SDL_mixer: ", Mix_GetError());
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

    SoundManager::GetInstance()->PlayMusic();
    SoundManager::GetInstance()->Load("next_level", "next_level.wav");
    SoundManager::GetInstance()->Load("dead", "dead.wav");
    SoundManager::GetInstance()->Load("jump", "jump.wav");

    TextManager::GetInstance()->Load("level", "LEVEL:" + std::to_string(currentLevel), {0, 0, 0});
    TextManager::GetInstance()->Load("deaths", "DEATHS:" + std::to_string(deaths), {255, 111, 51});

    TextureManager::GetInstance()->Load("bg", "/maps/bg-" + std::to_string(currentLevel) + ".bmp");

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
    score = new Score(new Props("fish", 1856, 416, 32, 32));

    Camera::GetInstance()->SetTarget(player->GetOrigin());

    return isRunning = true;
}

bool Engine::Clean() {
    TextureManager::GetInstance()->Clean();
    TextManager::GetInstance()->Clean();
    SoundManager::GetInstance()->Clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
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
    SoundManager::GetInstance()->Update();
    if (CollisionHandler::GetInstance()->CheckCollision(player->collider->Get(), score->collider->Get())) {
        NextLevel();
    }
    player->Update(dt);
    Camera::GetInstance()->Update(dt);

}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);
    SDL_RenderClear(renderer);

    TextureManager::GetInstance()->DrawBg("bg", 0, 0, 1980, SCREEN_HEIGHT);

    TextManager::GetInstance()->Draw("level", 10, 10);
    TextManager::GetInstance()->Draw("deaths", 700, 10);


    level->Render();

    score->Draw();
    player->Draw();


    SDL_RenderPresent(renderer);
}

void Engine::Events() {
    InputHandler::GetInstance()->Listen();
}

void Engine::NextLevel() {
    currentLevel++;
    SoundManager::GetInstance()->PlaySound("next_level");
    score->Next("LEVEL-" + std::to_string(currentLevel));
    //TODO: handle it somewhere else, create methods to handle it, create methods to reset it
    if (currentLevel == 5) {
        player->rigidBody->SetGravity(2.5f);
        player->jumpForce = 13.0f;
        player->jumpTime = 30.0f;
        player->jumpTimeReset = 30.0f;
    }
    player->transform->Set(20, 400);
    level = MapParser::GetInstance()->GetMap("LEVEL-" + std::to_string(currentLevel));
    TextManager::GetInstance()->Remove("level");
    TextManager::GetInstance()->Load("level", "LEVEL:" + std::to_string(currentLevel), {0, 0, 0});
    CollisionHandler::GetInstance()->UpdateMapCollision();
    TextureManager::GetInstance()->Remove("bg");
    TextureManager::GetInstance()->Load("bg", "/maps/bg-" + std::to_string(currentLevel) + ".bmp");
}

void Engine::RestartLevel() {
    deaths++;
    SoundManager::GetInstance()->PlaySound("dead");
    player->transform->Set(20, 400);
    TextManager::GetInstance()->Remove("deaths");
    TextManager::GetInstance()->Load("deaths", "DEATHS:" + std::to_string(deaths), {255, 111, 51});
}
