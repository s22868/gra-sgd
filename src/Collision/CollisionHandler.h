#ifndef GRASGD_COLLISIONHANDLER_H
#define GRASGD_COLLISIONHANDLER_H


#include "SDL.h"
#include "../Map/Tile.h"

class CollisionHandler {
public:
    bool CheckCollision(SDL_Rect a, SDL_Rect b);

    bool MapCollision(SDL_Rect a);

    void UpdateMapCollision();

    inline static CollisionHandler *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler();
    }

private:
    CollisionHandler();

    static CollisionHandler *s_Instance;
    TileMap collisionTilemapLayer;
    Tile* collisionTileLayer;
};


#endif //GRASGD_COLLISIONHANDLER_H
