#ifndef GRASGD_COLLIDER_H
#define GRASGD_COLLIDER_H

#include "SDL.h"

class Collider {
public:
    inline SDL_Rect Get() {
        return box;
    }

    inline void setPadding(int x, int y, int w, int h) {
        padding = {x, y, w, h};
    }

    void Set(int x, int y, int w, int h) {
        box = {
                x - padding.x,
                y - padding.y,
                w - padding.w,
                h - padding.h
        };
    }

private:
    SDL_Rect box;
    SDL_Rect padding;
};

#endif //GRASGD_COLLIDER_H
