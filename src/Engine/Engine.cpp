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


Engine *Engine::s_Instance = nullptr;
Player *player = nullptr;

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Nie udalo sie zaladowac SDL, %s", SDL_GetError());
        return false;
    }

    if(TTF_Init() < 0){
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


    TextureManager::GetInstance()->Load("bg", "test.bmp");

    if(!MapParser::GetInstance()->Load()){
        SDL_Log("Nie udalo sie zaladowac mapy");
    }

    level = MapParser::GetInstance()->GetMap("LEVEL-1");

    TextureManager::GetInstance()->Load("player_idle", "player-idle.bmp");
    TextureManager::GetInstance()->Load("player_run", "player-run.bmp");
    //TODO: Jump animation

//    TextureManager::GetInstance()->Load("player_jump", "player-jump.bmp");

    player = new Player(new Props("player_idle", 20, 400, 64, 32));

    Camera::GetInstance()->SetTarget(player->GetOrigin());

    return isRunning = true;
}

bool Engine::Clean() {
    TextureManager::GetInstance()->Clean();
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
//    level->Update();
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 124, 218, 254, 255);
    SDL_RenderClear(renderer);

    TextureManager::GetInstance()->Draw("bg", 100, 100, 742, 349);

    level->Render();

    //test font
    //TODO: add score gameobject
//    TTF_Font* font;
//
//    font = TTF_OpenFont("t_n_r.ttf", 24);
//    if ( !font ) {
//        SDL_Log("Failed to load font: %s", TTF_GetError());
//    }
//
//    SDL_Surface* text;
//// Set color to black
//    SDL_Color color = { 0, 0, 0 };
//
//    text = TTF_RenderText_Solid( font, "0 pkt", color );
//    if ( !text ) {
//        SDL_Log( "Failed to render text: %s", TTF_GetError());
//    }
//
//    SDL_Texture* text_texture;
//
//    text_texture = SDL_CreateTextureFromSurface( renderer, text );
//
//    SDL_Rect dest = { 0, 0, text->w, text->h };
//    SDL_Rect src = { 870, 20, text->w, text->h };
//
//    SDL_RenderCopy( renderer, text_texture, &dest, &src );
//
//    SDL_DestroyTexture( text_texture );
//    SDL_FreeSurface( text );

    player->Draw();



    SDL_RenderPresent(renderer);
}

void Engine::Events() {
    InputHandler::GetInstance()->Listen();
}
