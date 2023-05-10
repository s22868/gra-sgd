//
// Created by Mateusz on 09.05.2023.
//

#ifndef GRASGD_PLAYER_H
#define GRASGD_PLAYER_H


#include "Hero.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Collision/Collider.h"

#define JUMP_TIME 15.0f;
#define JUMP_FORCE 10.0f;

class Player : public Hero {
public:
    Player(Props *props);

    virtual void Draw();

    virtual void Clean();

    virtual void Update(float dt);

    virtual void AnimationHandler();

private:
    bool isRunning;
    bool isJumping;
    bool isGrounded;

    float jumpTime;
    float jumpForce;

    Animation* animation;
    RigidBody* rigidBody;

    Collider* collider;
    Vector2D lastSafePosition;
};


#endif //GRASGD_PLAYER_H