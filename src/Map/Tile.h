//
// Created by Mateusz on 07.05.2023.
//

#ifndef GRASGD_TILE_H
#define GRASGD_TILE_H

#include <string>
#include <vector>
#include "Layer.h"

struct Tileset {
    int FirstId, LastId, NumRows, NumCols, TileCount, TileSize;
    std::string Name, Source;
};

using TilesetsList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class Tile : public Layer {
public:
    Tile(int tileSizeParam, int numRowsParam, int numColParam, TileMap tileMapParam, TilesetsList tilesetsParam);

    virtual void Render();

    virtual void Update();

    inline TileMap GetTileMap() {
        return tileMap;
    }

private:
    int tileSize;
    int numRows, numCols;
    TileMap tileMap;
    TilesetsList tilesets;
};


#endif //GRASGD_TILE_H
