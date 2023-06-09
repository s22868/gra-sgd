//
// Created by Mateusz on 10.05.2023.
//

#include "Score.h"
#include "../Textures/TextureManager.h"
#include <iostream>

Score::Score(Props *props) : GameObject(props) {
    collider = new Collider();
    collider->Set(transform->X, transform->Y, width, height);
    winningCords["LEVEL-1"] = new Point(transform->X, transform->Y);
    winningCords["LEVEL-2"] = new Point(2816, 416);
    winningCords["LEVEL-3"] = new Point(3744, 192);
    winningCords["LEVEL-4"] = new Point(3232, 576);
    winningCords["LEVEL-5"] = new Point(3680, 512);
}

void Score::Draw() {
    TextureManager::GetInstance()->Draw(textureId, transform->X, transform->Y, width, height, flip);
}

void Score::Next(std::string level) {
    transform->Set(winningCords[level]->X, winningCords[level]->Y);
    collider->Set(transform->X, transform->Y, width, height);
}

void Score::Update(float dt) {

}

void Score::Clean() {
    TextureManager::GetInstance()->Remove("fish");
}

