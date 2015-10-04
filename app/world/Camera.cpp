#include "Camera.h"

#include "WorldObject.h"

Camera::Camera() : Movable()
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

void Camera::moveStarted()
{

}

void Camera::moveStopped()
{

}
