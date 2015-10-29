//
// Created by anderson on 26.10.15.
//

#ifndef APP_VISIBILITYTRACER_H
#define APP_VISIBILITYTRACER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Registry.h>
#include <world/WorldObject.h>
#include "customtypes.h"

class VisibilityTracer : public Registry {
public:
    VisibilityTracer(WorldObjectList objects);

    virtual std::string getType();

    VectorList calculateVisibility(WorldObject *viewer, sf::RenderWindow *window, float fov = 0);

//    bool filterVisibleObjects(WorldObject *viewer, WorldObjectList objects);

    bool isPointInPoly(sf::Vector2f origin, VectorList points);

    struct point_t {
        sf::Vector2f coords;
        struct point_t *pair;
        double angle;

        point_t(sf::Vector2f _coords, double _angle) : coords(_coords), angle(_angle) {
        }
    };

    static double getAngle(sf::Vector2f origin, sf::Vector2f other);

private:
    WorldObjectList objects;

    sf::Vector2f *getIntersection(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
};


#endif //APP_VISIBILITYTRACER_H
