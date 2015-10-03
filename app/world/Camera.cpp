#include "Camera.h"

#include "WorldObject.h"

Camera::Camera()
{

}

void Camera::attachTo(WorldObject *target)
{
    this->target = target;
}

void Camera::update()
{
    Movable::update();
    this->position = this->target->position;
    this->rotation = this->target->rotation;
}
