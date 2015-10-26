//
// Created by anderson on 26.10.15.
//

#include <SFML/System/Vector2.hpp>
#include "VisibilityTracer.h"
#include "world/WorldObject.h"

VisibilityTracer::VisibilityTracer(WorldObjectList objects) : objects(objects) {
}

VectorList VisibilityTracer::calculateVisibility(WorldObject *viewer) {
    struct {
        sf::Vector2f viewerPos;

        double getAngle(sf::Vector2f origin, sf::Vector2f other) {
            float dx = other.x - origin.x;
            float dy = other.y - origin.y;
            return atan2(dy, dx);
        }

        bool operator() (const sf::Vector2f a, const sf::Vector2f b) {
            return getAngle(viewerPos, a) > getAngle(viewerPos, b);
        }
    } sortStruct;

    sortStruct.viewerPos = viewer->getWPosition();

    VectorList result;
    for (WorldObject *object : this->objects) {
        if (object != viewer) {
            sf::FloatRect hitbox = object->getWHitbox();
            result.push_back(sf::Vector2f(hitbox.left, hitbox.top));
            result.push_back(sf::Vector2f(hitbox.left + hitbox.width, hitbox.top));
            result.push_back(sf::Vector2f(hitbox.left, hitbox.top + hitbox.height));
            result.push_back(sf::Vector2f(hitbox.left + hitbox.width, hitbox.top + hitbox.height));
        }
    }

    std::sort(result.begin(), result.end(), sortStruct);

    return result;
}

