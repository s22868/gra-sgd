
#include <SDL.h>
#include "Time.h"

float const SECOND = 1000.0f;
Time *Time::s_Instance = nullptr;

void Time::Tick() {
    deltaTime = (SDL_GetTicks() - lastTime) * (TARGET_FPS / SECOND);
    if(deltaTime>TARGET_DELTATIME){
        deltaTime = TARGET_DELTATIME;
    }
    lastTime = SDL_GetTicks();
}
