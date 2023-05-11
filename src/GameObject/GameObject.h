//
// Created by Mateusz on 04.05.2023.
//

#ifndef GRASGD_GAMEOBJECT_H
#define GRASGD_GAMEOBJECT_H

#include <string>
#include <SDL.h>
#include "../Physics/Transform.h"
#include "../Physics/Point.h"

struct Props {
public:
    int Width, Height;
    float X, Y;
    std::string TextureId;
    SDL_RendererFlip Flip;

    Props(std::string textureId, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        TextureId = textureId;
    }
};

class GameObject {
public:
    GameObject(Props *props) : textureId(props->TextureId),
                               width(props->Width),
                               height(props->Height),
                               flip(props->Flip) {
        transform = new Transform(props->X, props->Y);
        float px = props->X + props->Width/2;
        float py = props->Y + props->Height/2;
        origin = new Point(px, py);
    };

    inline Point* GetOrigin(){
        return origin;
    }

    virtual void Draw() = 0;

    virtual void Clean() = 0;

    virtual void Update(float dt) = 0;

    Transform *transform;
protected:
    Point* origin;
    int width, height;
    std::string textureId;
    SDL_RendererFlip flip;
};

#endif //GRASGD_GAMEOBJECT_H
