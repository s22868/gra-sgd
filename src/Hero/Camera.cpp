
#include "Camera.h"

Camera *Camera::s_Instance = nullptr;

void Camera::Update(float dt) {
    if (target != nullptr) {

        //start move camera from mid screen

        viewRectangle.x = target->X - SCREEN_WIDTH / 2;
        viewRectangle.y = target->Y - SCREEN_HEIGHT / 2;

        if (viewRectangle.x < 0) {
            viewRectangle.x = 0;
        }
        if (viewRectangle.y < 0) {
            viewRectangle.y = 0;
        }
        if (viewRectangle.y > (SCREEN_HEIGHT - viewRectangle.h)) {
            viewRectangle.y = (SCREEN_HEIGHT - viewRectangle.h);
        }

        position = Vector2D(viewRectangle.x, viewRectangle.y);

    }
}
