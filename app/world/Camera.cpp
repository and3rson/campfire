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
    this->wPosition = this->target->wPosition;
    float rotDiff = this->target->wRotation - this->wRotation;
    this->wRotation += rotDiff / 4;
}

void Camera::moveStarted()
{

}

void Camera::moveStopped()
{

}

std::string Camera::getType() {
    return "camera";
}
