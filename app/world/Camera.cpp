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
    this->setWPosition(this->target->getWPosition());
    this->setWPosition(this->getWPosition() + this->rShift);
    float rotDiff = this->target->getWRotation() - this->getWRotation();
    this->setWRotation(this->getWRotation() + rotDiff / 4);
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
