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

void WorldObject::setWPosition(sf::Vector2f pos)
{
    this->wPosition = sf::Vector2f(pos);
}

sf::Vector2f WorldObject::getWPosition() {
    return this->wPosition;
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
    for (WorldObject *object : this->children) {
        if (object == other) {
            this->children.erase(std::remove(this->children.begin(), this->children.end(), object));
            object->parent = NULL;
//            this->children.erase(it);
        }
//        it++;
    }
}

//void WorldObject::addCollision(WorldObject *other) {
//    this->collisions.push_back(other);
//}
//
//void WorldObject::removeCollision(WorldObject *other) {
//    this->collisions.erase(std::remove(this->collisions.begin(), this->collisions.end(), other));
//}
//
//bool WorldObject::isColliding(WorldObject *other) {
//    for (WorldObject *object : this->collisions) {
//        if (object == other) {
//            return true;
//        }
//    }
//    return false;
//}

void WorldObject::setAsCurrent() {
    this->current = true;
}

bool WorldObject::getIsCurrent() {
    return this->current;
}

bool WorldObject::isPickable() {
    return false;
}

void WorldObject::setWRotation(float rotation) {
    this->wRotation = rotation;
}

float WorldObject::getWRotation() {
//    if (this->wRotation < 0) {
//        this->wRotation = this->wRotation + M_PI * 2;
//    }
//    if (this->wRotation > M_PI * 2) {
//        this->wRotation = this->wRotation - M_PI * 2;
//    }
    return this->wRotation;
}

float WorldObject::getDistance(sf::Vector2f a, sf::Vector2f b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

VectorList WorldObject::getWLightbox() {
    sf::FloatRect lightbox = this->oLightbox;

    if (!lightbox.width || !lightbox.height) {
        return VectorList();
    }

    VectorList points = {
        this->wPosition + WorldObject::rotateVector(sf::Vector2f(lightbox.left, lightbox.top), this->wRotation),
        this->wPosition + WorldObject::rotateVector(sf::Vector2f(lightbox.left + lightbox.width, lightbox.top), this->wRotation),
        this->wPosition + WorldObject::rotateVector(sf::Vector2f(lightbox.left + lightbox.width, lightbox.top + lightbox.height), this->wRotation),
        this->wPosition + WorldObject::rotateVector(sf::Vector2f(lightbox.left, lightbox.top + lightbox.height), this->wRotation)
    };

    return points;
}

WorldObject::Material WorldObject::getMaterial() {
    return NONE;
}

float WorldObject::getLength(sf::Vector2f a) {
    return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

sf::Vector2f WorldObject::normalize(sf::Vector2f a) {
    float length = WorldObject::getLength(a);
    if (length == 0) {
        return sf::Vector2f(0, 0);
    }
    return sf::Vector2f(a.x / length, a.y / length);
}

void WorldObject::draw(sf::RenderWindow *window) {

}
