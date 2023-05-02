#define SDL_MAIN_HANDLED

#include "src/Core/Engine.h"

int main() {
    Engine::GetInstance()->Init();
    while (Engine::GetInstance()->IsRunning()) {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
    }
    Engine::GetInstance()->Clean();

    return 0;
}