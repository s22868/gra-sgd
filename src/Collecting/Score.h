//
// Created by Mateusz on 10.05.2023.
//

#ifndef GRASGD_SCORE_H
#define GRASGD_SCORE_H


#include <map>
#include "../GameObject/GameObject.h"
#include "../Collision/Collider.h"


class Score : public GameObject {
public:
    Score(Props *props);

    virtual void Draw();

    virtual void Clean();

    virtual void Update(float dt);

    virtual void Next(std::string level);

    Collider *collider;

private:
    std::map<std::string, Point *> winningCords;
};


#endif //GRASGD_SCORE_H
