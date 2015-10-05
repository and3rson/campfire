#include "Camera.h"

#include "WorldObject.h"

Camera::Camera() : AMovable()
{

}

void Camera::attachTo(WorldObject *target)
{
    this->target = target;
}

void Camera::update()
{
    AMovable::update();
    this->position = this->target->position;
    float rotDiff = this->target->rotation - this->rotation;
    this->rotation += rotDiff / 4;
}

void Camera::moveStarted()
{

}

void Camera::moveStopped()
{

}
