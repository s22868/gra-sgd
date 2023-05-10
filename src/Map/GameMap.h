#ifndef GRASGD_GAMEMAP_H
#define GRASGD_GAMEMAP_H
#include <vector>
#include "Layer.h"

class GameMap {
public:
    void Render() {
        for (unsigned int i = 0; i < mapLayers.size(); i++) {
            mapLayers[i]->Render();
        }
    }

    void Update() {
        for (unsigned int i = 0; i < mapLayers.size(); i++) {
            mapLayers[i]->Update();
        }
    }

    std::vector<Layer *> GetMapLayers() {
        return mapLayers;
    }

private:
    friend class MapParser;

    std::vector<Layer *> mapLayers;


};

#endif //GRASGD_GAMEMAP_H
