#ifndef GRASGD_MAPPARSER_H
#define GRASGD_MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "Tile.h"
#include "../Vendor/TinyXML/tinyxml.h"

//singleton
class MapParser {
public:
    inline static MapParser *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
    }

    bool Load();

    void Clean();

    inline GameMap *GetMap(std::string id) {
        return maps[id];
    }

private:
    MapParser() {};

    static MapParser *s_Instance;

    std::map<std::string, GameMap *> maps;

    bool Parse(std::string id, std::string src);

    Tileset ParseTileset(TiXmlElement *xmlTileset);

    Tile *ParseTile(TiXmlElement *xmlLayer, TilesetsList tilesets, int tilesize, int numRows, int numCols);
};


#endif //GRASGD_MAPPARSER_H
