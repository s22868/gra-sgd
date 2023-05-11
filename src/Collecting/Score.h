//
// Created by Mateusz on 10.05.2023.
//

#ifndef GRASGD_SCORE_H
#define GRASGD_SCORE_H


#include "../GameObject/GameObject.h"
#include "../Collision/Collider.h"

class Score : public GameObject {
public:
    Score(Props *props);

    virtual void Draw();

    virtual void Clean();

    virtual void Update(float dt);

    virtual void Next();

    Collider *collider;

private:
};


#endif //GRASGD_SCORE_H
