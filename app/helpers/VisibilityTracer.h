//
// Created by anderson on 26.10.15.
//

#ifndef APP_VISIBILITYTRACER_H
#define APP_VISIBILITYTRACER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "customtypes.h"

class VisibilityTracer {
public:
    VisibilityTracer(WorldObjectList objects);

    VectorList calculateVisibility(WorldObject *viewer, sf::RenderWindow *window);

private:
    WorldObjectList objects;

    double getAngle(sf::Vector2f origin, sf::Vector2f other);
    sf::Vector2f *getIntersection(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
};


#endif //APP_VISIBILITYTRACER_H
