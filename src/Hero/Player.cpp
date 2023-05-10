//
// Created by Mateusz on 09.05.2023.
//

#include "Player.h"
#include "../Textures/TextureManager.h"
#include "../InputHandler/InputHandler.h"
#include "Camera.h"
#include "../Collision/CollisionHandler.h"

Player::Player(Props *props) : Hero(props) {

    isRunning = false;
    isGrounded = false;
    isJumping = false;

    jumpTime = JUMP_TIME;
    jumpForce = JUMP_FORCE;

    collider = new Collider();
    collider->setPadding(-20, -8, 40, 0);

    rigidBody = new RigidBody();
    rigidBody->SetGravity(3.0f);

    animation = new Animation();
    animation->SetProps(textureId, 1, 8, 160);
}

void Player::Draw() {
    animation->Draw(transform->X, transform->Y, width, height, flip);

    //check box collider
//    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 124, 0, 0, 255);
//    Vector2D cam = Camera::GetInstance()->GetPosition();
//    SDL_Rect box = collider->Get();
//    box.x -= cam.X;
//    box.y -= cam.Y;
//    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Player::Update(float dt) {
//    animation->SetProps(textureId, 1, 8, 160);
    rigidBody->RemoveForce();
    isRunning = false;

    //move
    if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        rigidBody->ApplyForceX(-10);
        flip = SDL_FLIP_HORIZONTAL;
        isRunning = true;
    }
    if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        rigidBody->ApplyForceX(10);
        flip = SDL_FLIP_NONE;
        isRunning = true;
    }

    //jump
    if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && isGrounded) {
        isJumping = true;
//        isGrounded = false;
        rigidBody->ApplyForceY(-jumpForce);
    }
    if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && isJumping && jumpTime > 0) {
        jumpTime -= dt;
        rigidBody->ApplyForceY(-jumpForce);
    } else {
        isJumping = false;
        jumpTime = JUMP_TIME
    }


    rigidBody->Update(dt);

    //move on X
    lastSafePosition.X = transform->X;
    transform->X += rigidBody->GetPosition().X;
    collider->Set(transform->X, transform->Y, 64, 24);

    if(CollisionHandler::GetInstance()->MapCollision(collider->Get())){
        transform->X = lastSafePosition.X;
    }

    //move on Y
    rigidBody->Update(dt);
    lastSafePosition.Y = transform->Y;
    transform->Y += rigidBody->GetPosition().Y;
    collider->Set(transform->X, transform->Y,64,24);

    if(CollisionHandler::GetInstance()->MapCollision(collider->Get())){
        isGrounded = true;
        transform->Y = lastSafePosition.Y;
    }else{
        isGrounded = false;
    }

    origin->X = transform->X + width / 2;
    origin->Y = transform->Y + height / 2;

    AnimationHandler();
    animation->Update();
}

void Player::AnimationHandler() {
    animation->SetProps("player_idle", 1, 8, 160);

    if(isRunning){
        animation->SetProps("player_run", 1, 8, 160);
    }
//    TODO:
//    if(isJumping)

}

void Player::Clean() {
    TextureManager::GetInstance()->Remove(textureId);
}


