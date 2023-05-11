#include "MapParser.h"

MapParser *MapParser::s_Instance = nullptr;

bool MapParser::Load() {
    return Parse("LEVEL-1", "assets/maps/level-1.tmx") && Parse("LEVEL-2", "assets/maps/level-2.tmx") && Parse("LEVEL-3", "assets/maps/level-1.tmx");
}


bool MapParser::Parse(std::string id, std::string src) {
    TiXmlDocument xml;
    xml.LoadFile(src);

    if (xml.Error()) {
        return false;
    }
    TiXmlElement *root = xml.RootElement();
    int numrows, numcols, tilesize = 0;
    root->Attribute("width", &numcols);
    root->Attribute("height", &numrows);
    root->Attribute("tilewidth", &tilesize);

    //parse tilesets
    TilesetsList tilesets;
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            tilesets.push_back(ParseTileset(e));
        }
    }


    //parse layers
    GameMap *gameMap = new GameMap();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            Tile *tilelayer = ParseTile(e, tilesets, tilesize, numrows, numcols);
            gameMap->mapLayers.push_back(tilelayer);
        }
    }
    maps[id] = gameMap;
    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement *xmlTileset) {
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstId);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastId = (tileset.FirstId + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.NumCols);
    tileset.NumRows = tileset.TileCount / tileset.NumCols;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement *image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");

    return tileset;
}

Tile *MapParser::ParseTile(TiXmlElement *xmlLayer, TilesetsList tilesets, int tilesize, int numRows, int numCols) {
    TiXmlElement *data;
    for (TiXmlElement *elem = xmlLayer->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        if (elem->Value() == std::string("data")) {
            data = elem;
            break;
        }
    }

    //Parse Layer tile map  ----        matrix-> 0,0,0,id,0,id,0,id -> level-1.tmx Layer
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(numRows, std::vector<int>(numCols, 0));
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];
            if (!iss.good()) {
                break;
            }
        }
    }
    return (new Tile(tilesize, numRows, numCols, tilemap, tilesets));
}


void MapParser::Clean() {
    std::map<std::string, GameMap *>::iterator it;
    for (it = maps.begin(); it != maps.end(); it++) {
        it->second = nullptr;
    }
    maps.clear();
}