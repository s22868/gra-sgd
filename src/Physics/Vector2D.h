//
// Created by Mateusz on 03.05.2023.
//

#ifndef GRASGD_VECTOR2D_H
#define GRASGD_VECTOR2D_H


class Vector2D {
public:
    float X, Y;

    Vector2D(float x = 0, float y = 0) : X(x), Y(y) {};

    inline Vector2D operator+(const Vector2D &v2) const {
        return {X + v2.X, Y + v2.Y};
    }

    inline Vector2D operator-(const Vector2D &v2) const {
        return {X - v2.X, Y - v2.Y};
    }

    inline Vector2D operator*(const float multi) const {
        return {X * multi, Y * multi};
    }

};

#endif //GRASGD_VECTOR2D_H
