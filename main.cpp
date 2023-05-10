#define SDL_MAIN_HANDLED

#include "src/Engine/Engine.h"
#include "src/Time/Time.h"

int main() {
    Engine::GetInstance()->Init();
    while (Engine::GetInstance()->IsRunning()) {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Time::GetInstance()->Tick();
    }
    Engine::GetInstance()->Clean();

    return 0;
}