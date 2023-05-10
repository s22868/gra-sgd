//
// Created by Mateusz on 09.05.2023.
//

#ifndef GRASGD_HERO_H
#define GRASGD_HERO_H

#include "../GameObject/GameObject.h"

class Hero : public GameObject {
public:
    Hero(Props *props) : GameObject(props) {}

    virtual void Draw() = 0;

    virtual void Clean() = 0;

    virtual void Update(float dt) = 0;

protected:
    std::string name;
};

#endif //GRASGD_HERO_H
