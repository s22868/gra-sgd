//
// Created by Mateusz on 09.05.2023.
//

#ifndef GRASGD_PLAYER_H
#define GRASGD_PLAYER_H


#include "Hero.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Collision/Collider.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 20.0f
#define MOVE_FORCE 13.0f

class Player : public Hero {
public:
    Player(Props *props);

    virtual void Draw();

    virtual void Clean();

    virtual void Update(float dt);

    virtual void AnimationHandler();

    Collider* collider;

private:
    friend class Engine;
    bool isRunning;
    bool isJumping;
    bool isGrounded;

    float jumpTimeReset;
    float jumpTime;
    float jumpForce;

    Animation* animation;
    RigidBody* rigidBody;

    Vector2D lastSafePosition;
};


#endif //GRASGD_PLAYER_H
