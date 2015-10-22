#include <GameEngine.h>
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

//    float cs = cos(-camera->wRotation);
//    float sn = sin(-camera->wRotation);
//
//    int x = vector.x * cs - vector.y * sn;
//    int y = vector.x * sn + vector.y * cs;

    sf::Vector2f rotated = WorldObject::rotateVector(vector, -camera->wRotation);

    sf::Vector2u windowSize = GameEngine::getInstance()->getWindow()->getSize();

    return sf::Vector2f(rotated.x + windowSize.x / 2, rotated.y + windowSize.y / 2);
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

sf::Vector2f WorldObject::rotateVector(sf::Vector2f vector, float angle) {
    float cs = cos(angle);
    float sn = sin(angle);

    float x = vector.x * cs - vector.y * sn;
    float y = vector.x * sn + vector.y * cs;

    return sf::Vector2f(x, y);
}

bool WorldObject::collisionStarted(WorldObject *other) {
    return false;
}

bool WorldObject::collisionStopped(WorldObject *other) {
    return false;
}

bool WorldObject::isCollidable() {
    return true;
}

WorldObjectList WorldObject::getChildren() {
    return this->children;
}

void WorldObject::addChild(WorldObject *object) {
    // TODO: Check if object already has a parent
    this->children.push_back(object);
    object->parent = this;
}

void WorldObject::removeChild(WorldObject *other) {
//    WorldObjectList::iterator it = this->children.begin();
    std::cerr << "Before count: " << this->children.size() << std::endl;
    for (WorldObject *object : this->children) {
        if (object == other) {
            this->children.erase(std::remove(this->children.begin(), this->children.end(), object));
            object->parent = NULL;
//            this->children.erase(it);
        }
//        it++;
    }
    std::cerr << "New child count: " << this->children.size() << std::endl;
}

void WorldObject::addCollision(WorldObject *other) {
    this->collisions.push_back(other);
}

void WorldObject::removeCollision(WorldObject *other) {
    this->collisions.erase(std::remove(this->collisions.begin(), this->collisions.end(), other));
}

bool WorldObject::isColliding(WorldObject *other) {
    for (WorldObject *object : this->collisions) {
        if (object == other) {
            return true;
        }
    }
    return false;
}

void WorldObject::setAsCurrent() {
    this->current = true;
}

bool WorldObject::getIsCurrent() {
    return this->current;
}

bool WorldObject::isPickable() {
    return false;
}
