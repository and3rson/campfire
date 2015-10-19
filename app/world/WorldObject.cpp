#include "WorldObject.h"
#include "Camera.h"

WorldObject::WorldObject(Camera *camera) : camera(camera)
{
    this->wPosition = sf::Vector2f(0, 0);
}

void WorldObject::update()
{
    // Nothing
}

void WorldObject::setPosition(sf::Vector2f pos)
{
    this->wPosition = sf::Vector2f(pos);
}

sf::Vector2f WorldObject::applyCameraTransformation(sf::Vector2f pos)
{
    sf::Vector2f vector = pos - this->camera->wPosition;
//    float angle = atan2(vector.y, vector.x);
//    std::cerr << angle;

    float cs = cos(-camera->wRotation);
    float sn = sin(-camera->wRotation);

    int x = vector.x * cs - vector.y * sn;
    int y = vector.x * sn + vector.y * cs;

    return sf::Vector2f(x + 400, y + 320);
}

sf::FloatRect WorldObject::getWHitbox() {
    return sf::FloatRect(
            this->wPosition.x + this->oHitbox.left,
            this->wPosition.y + this->oHitbox.top,
            this->oHitbox.width,
            this->oHitbox.height
    );
}

std::string WorldObject::getType() {
    return "object";
}
