//
// Created by Mateusz on 10.05.2023.
//

#include "Score.h"
#include "../Textures/TextureManager.h"
#include <iostream>

Score::Score(Props *props) : GameObject(props) {
    collider = new Collider();
    collider->Set(transform->X, transform->Y, width, height);
}

void Score::Draw() {
    TextureManager::GetInstance()->Draw(textureId, transform->X, transform->Y, width, height, flip);
}

void Score::Next(){
    transform->Set(300, 400);
    collider->Set(transform->X, transform->Y, width, height);
}

void Score::Update(float dt) {

}

void Score::Clean() {
    TextureManager::GetInstance()->Remove("fish");
}

