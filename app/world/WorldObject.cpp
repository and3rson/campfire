#include "WorldObject.h"
#include "Camera.h"

WorldObject::WorldObject(Camera *camera) : camera(camera)
{
    this->position = sf::Vector2f(0, 0);
}

void WorldObject::update()
{
    // Nothing
}

void WorldObject::setPosition(sf::Vector2f pos)
{
    this->position = sf::Vector2f(pos);
}

sf::Vector2f WorldObject::applyCameraTransformation(sf::Vector2f pos)
{
    sf::Vector2f vector = pos - this->camera->position;
//    float angle = atan2(vector.y, vector.x);
//    std::cerr << angle;

    float cs = cos(-camera->rotation);
    float sn = sin(-camera->rotation);

    int x = vector.x * cs - vector.y * sn;
    int y = vector.x * sn + vector.y * cs;

    return sf::Vector2f(x + 400, y + 320);
}
