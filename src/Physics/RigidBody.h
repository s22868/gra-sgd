#ifndef GRASGD_RIGIDBODY_H
#define GRASGD_RIGIDBODY_H

#include "Vector2D.h"

#define DEFAULT_MASS 1.0f
#define DEFAULT_GRAVITY 9.8f

class RigidBody {
public:
    RigidBody() {
        mass = DEFAULT_MASS;
        gravity = DEFAULT_GRAVITY;
    };

    inline void SetMass(float massParam) { mass = massParam; }

    inline void SetGravity(float gravityParam) { gravity = gravityParam; }


    inline void ApplyForce(Vector2D forceParam) {
        force = forceParam;
    }

    inline void ApplyForceX(float forceX) {
        force.X = forceX;
    }

    inline void ApplyForceY(float forceY) {
        force.Y = forceY;
    }

    inline void RemoveForce() {
        force = Vector2D(0, 0);
    }


    inline void ApplyFriction(Vector2D frictionParam) {
        friction = frictionParam;
    }

    inline void RemoveFriction() {
        friction = Vector2D(0, 0);
    }

    inline float GetMass() { return mass; }

    inline Vector2D GetPosition() { return position; }

    inline Vector2D GetVelocity() { return velocity; }

    inline Vector2D GetAcceleration() { return acceleration; }

    void Update(float dt) {
        acceleration.X = (force.X + friction.X) / mass;
        acceleration.Y = gravity + force.Y / mass;
        velocity = acceleration * dt;
        position = velocity * dt;
    }

private:
    float mass;
    float gravity;

    Vector2D force;
    Vector2D friction;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

};

#endif //GRASGD_RIGIDBODY_H
