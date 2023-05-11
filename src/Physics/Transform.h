//
// Created by Mateusz on 04.05.2023.
//

#ifndef GRASGD_TRANSFORM_H
#define GRASGD_TRANSFORM_H

#include "Vector2D.h"

class Transform {
public:
    float X, Y;

    Transform(float x = 0, float y = 0) : X(x), Y(y) {};

    inline void TranslateX(float x) { X += x; }

    inline void TranslateY(float y) { Y += y; }

    inline void Translate(Vector2D v) {
        X += v.X;
        Y += v.Y;
    }

    inline void Set(float x, float y) {
        X = x;
        Y = y;
    };

};

#endif //GRASGD_TRANSFORM_H
