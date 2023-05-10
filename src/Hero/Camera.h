#ifndef GRASGD_CAMERA_H
#define GRASGD_CAMERA_H

#include "SDL.h"
#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"
#include "../Engine/Engine.h"

//singleton
class Camera {
public:
    inline static Camera *GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
    }

    inline SDL_Rect GetViewRectangle() {
        return viewRectangle;
    }

    inline Vector2D GetPosition() {
        return position;
    }

    inline void SetTarget(Point *targetParam) {
        target = targetParam;
    }

    void Update(float dt);

private:
    Camera() { viewRectangle = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; };

    Point *target;
    Vector2D position;

    SDL_Rect viewRectangle;

    static Camera *s_Instance;
};


#endif //GRASGD_CAMERA_H
