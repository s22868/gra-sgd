#define SDL_MAIN_HANDLED
#include <SDL.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Gra SGD",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   640, 480,
                                   SDL_WINDOW_SHOWN);
    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}