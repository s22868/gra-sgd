#include "Tile.h"
#include "../Textures/TextureManager.h"

Tile::Tile(int tileSizeParam, int numRowsParam, int numColParam, TileMap tileMapParam, TilesetsList tilesetsParam)
        : tileSize(tileSizeParam), numCols(numColParam), numRows(numRowsParam), tileMap(tileMapParam), tilesets(tilesetsParam) {
    for(unsigned int i=0; i<tilesets.size(); i++){
        TextureManager::GetInstance()->Load(tilesets[i].Name, "maps/" + tilesets[i].Source);
    }

}

void Tile::Render() {
    for (unsigned int i = 0; i < numRows; i++) {
        for (unsigned int j = 0; j < numCols; j++) {
            int tileId = tileMap[i][j];

            if (tileId == 0) {
                continue;
            }

            int index = 0;
            //convert to real id -- Tiled -> tilesets editor -> xxx -> xx ex. 423 -> 11
            if (tilesets.size() > 1) {
                for (unsigned int k = 1; k < tilesets.size(); k++) {
                    if (tileId >= tilesets[k].FirstId && tileId <= tilesets[k].LastId) {
                        tileId = tileId + tilesets[k].TileCount - tilesets[k].LastId;
                        index = k;
                        break;
                    }
                }
            }
            //get row and col of tileset index
            Tileset ts = tilesets[index];
            int tileRow = tileId / ts.NumCols;
            int tileCol = tileId - tileRow * ts.NumCols - 1;

            //remove last row if its empty
            //ex -> x is tile e is empty -> remove empty tiles
            //x,x,x,e
            //x,x,x,e
            //x,e,e,e

            if (tileId % ts.NumCols == 0) {
                tileRow--;
                tileCol = ts.NumCols - 1;
            }

            TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j*ts.TileSize, i*ts.TileSize, tileRow, tileCol);

        }
    }
}

void Tile::Update() {

}
