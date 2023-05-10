//
// Created by Mateusz on 03.05.2023.
//

#ifndef GRASGD_INPUTHANDLER_H
#define GRASGD_INPUTHANDLER_H

#include <SDL.h>

//singleton
class InputHandler {
public:
    static InputHandler *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new InputHandler();
    }

    void Listen();

    bool GetKeyDown(SDL_Scancode key);

private:
    InputHandler();

    void KeyUp();

    void KeyDown();

    const Uint8 *keyStates;
    static InputHandler *s_Instance;
};


#endif //GRASGD_INPUTHANDLER_H
