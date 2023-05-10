//
// Created by Mateusz on 03.05.2023.
//

#include "InputHandler.h"
#include "../Engine/Engine.h"

InputHandler *InputHandler::s_Instance = nullptr;

InputHandler::InputHandler() {
    keyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::Listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Engine::GetInstance()->Quit();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
        }
    }
}

bool InputHandler::GetKeyDown(SDL_Scancode key) {
    return (keyStates[key] == 1);
}


void InputHandler::KeyUp() {
    keyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::KeyDown() {
    keyStates = SDL_GetKeyboardState(nullptr);
}
