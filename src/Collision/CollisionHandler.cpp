
#include "CollisionHandler.h"
#include "../Engine/Engine.h"

CollisionHandler *CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
    //                                                                --first layer in Tiled will be collision layer (collision) .front() from vector
    collisionTileLayer = (Tile *) Engine::GetInstance()->GetMap()->GetMapLayers().front();
    collisionTilemapLayer = collisionTileLayer->GetTileMap();
}


bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
    bool x_overlap = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlap = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlap && y_overlap);
}

bool CollisionHandler::MapCollision(SDL_Rect a) {

    int tileSize = 32;
    int numRows = 20;
    int numCols = 60;

    int leftTile = a.x / tileSize;
    int rightTile = (a.x + a.w) / tileSize;

    int topTile = a.y / tileSize;
    int bottomTile = (a.y + a.h) / tileSize;

    if (leftTile < 0) leftTile = 0;
    if (rightTile > numCols) rightTile = numCols;

    if (topTile < 0) topTile = 0;
    if (bottomTile > numRows) bottomTile = numRows;

    for (int i = leftTile; i <= rightTile; ++i) {
        for (int j = topTile; j <= bottomTile; ++j) {
            if (collisionTilemapLayer[j][i] > 0) {
                return true;
            }
        }
    }

    return false;
}
