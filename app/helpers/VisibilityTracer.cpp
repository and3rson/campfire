//
// Created by anderson on 26.10.15.
//

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "VisibilityTracer.h"
#include "world/WorldObject.h"

VisibilityTracer::VisibilityTracer(WorldObjectList objects) : objects(objects) {
}

VectorList VisibilityTracer::calculateVisibility(WorldObject *viewer, sf::RenderWindow *window) {
    struct point_t {
        int id;
        sf::Vector2f coords;
        bool isStart;
        struct point_t *pair;
        double angle;

        point_t(int _id, sf::Vector2f _coords, double _angle) : id(_id), coords(_coords), angle(_angle) {
        }

//        bool operator==(point_t *other) {
//            return id == other->id;
//        }
    };

    struct {
        sf::Vector2f viewerPos;

        double getAngle(sf::Vector2f origin, sf::Vector2f other) {
            float dx = other.x - origin.x;
            float dy = other.y - origin.y;
            return atan2(dy, dx);
        }

        bool operator() (point_t *a, point_t *b) {
            return getAngle(viewerPos, a->coords) > getAngle(viewerPos, b->coords);
        }
    } sortStruct;

    sortStruct.viewerPos = viewer->getWPosition();

    struct {
        sf::Vector2f viewerPos;
        double angle;

        sf::Vector2f *getIntersection(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
            float s1_x = p1.x - p0.x;
            float s1_y = p1.y - p0.y;
            float s2_x = p3.x - p2.x;
            float s2_y = p3.y - p2.y;

//                if(p0.isSame(p2) || p0.isSame(p3)) {
//                    return p0;
//                }
//
//                if(p1.isSame(p2) || p1.isSame(p3)) {
//                    return p1;
//                }

            float s = (-s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y)) / (-s2_x * s1_y + s1_x * s2_y);
            float t = ( s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x)) / (-s2_x * s1_y + s1_x * s2_y);

            if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
                // Collision detected
                float i_x = p0.x + (t * s1_x);
                float i_y = p0.y + (t * s1_y);
                return new sf::Vector2f(i_x, i_y);
            }
            return NULL;
        }

        bool operator() (point_t *a, point_t *b) {
            sf::Vector2f *i = getIntersection(sf::Vector2f(0, 0), sf::Vector2f(5, 5), sf::Vector2f(0, 2), sf::Vector2f(5, 3));
            sf::Vector2f rayEnd = WorldObject::rotateVector(sf::Vector2f(0, -1000), - angle + M_PI / 2);

            std::cerr << angle << std::endl;
            std::cerr << a->coords.x << "/" << a->coords.y << ", " << a->pair->coords.x << "/" << a->pair->coords.y << std::endl;
            std::cerr << b->coords.x << "/" << b->coords.y << ", " << b->pair->coords.x << "/" << b->pair->coords.y << std::endl;
            std::cerr << viewerPos.x << "/" << viewerPos.y << ", " << rayEnd.x << "/" << rayEnd.y << std::endl;

            sf::Vector2f *intersection1 = getIntersection(viewerPos, rayEnd, a->coords, a->pair->coords);
            sf::Vector2f *intersection2 = getIntersection(viewerPos, rayEnd, b->coords, b->pair->coords);
            if (!intersection1 || !intersection2) {
                throw "DAFUQ?!";
            }
            bool result = WorldObject::getDistance(viewerPos, *intersection1) > WorldObject::getDistance(viewerPos, *intersection2);
            delete intersection1;
            delete intersection2;
            return result;
        }
    } sortWallStruct;

    sortWallStruct.viewerPos = viewer->getWPosition();

//    struct wall_t {
//        sf::Vector2f start;
//        sf::Vector2f end;
////        double distance;
//        double angles[2];
//    };

    std::vector<point_t*> points;

    sf::Vector2f viewerPos = viewer->getWPosition();

    VectorList result;
    int id = 0;
    for (WorldObject *object : this->objects) {
        if (object != viewer) {
            sf::FloatRect hitbox = object->getWHitbox();

            sf::Vector2f lines[] = {
                sf::Vector2f(hitbox.left, hitbox.top),
                sf::Vector2f(hitbox.left + hitbox.width, hitbox.top),
                sf::Vector2f(hitbox.left + hitbox.width, hitbox.top + hitbox.height),
                sf::Vector2f(hitbox.left, hitbox.top + hitbox.height),
            };

            for (int i = 0; i < 4; i++) {
                sf::Vector2f start = lines[i];
                sf::Vector2f end = lines[(i + 1) % 4];

                double angle1 = this->getAngle(viewerPos, start);
                double angle2 = this->getAngle(viewerPos, end);

                point_t *startPoint = new point_t(id++, start, angle1);
                point_t *endPoint = new point_t(id++, end, angle2);

                if (angle1 > angle2) {
                    point_t *temp = startPoint;
                    startPoint = endPoint;
                    endPoint = temp;
                }

                startPoint->isStart = true;
                endPoint->isStart = false;

                startPoint->pair = endPoint;
                endPoint->pair = startPoint;

                points.push_back(startPoint);
                points.push_back(endPoint);

                sf::Vertex line[] = {
                    sf::Vertex(viewer->applyCameraTransformation(start), sf::Color::Red),
                    sf::Vertex(viewer->applyCameraTransformation(end), sf::Color::Green)
                };
                window->draw(line, 2, sf::Lines);

//                walls.push_back(wall);
            }

//            result.push_back(sf::Vector2f(hitbox.left, hitbox.top));
//            result.push_back(sf::Vector2f(hitbox.left + hitbox.width, hitbox.top));
//            result.push_back(sf::Vector2f(hitbox.left, hitbox.top + hitbox.height));
//            result.push_back(sf::Vector2f(hitbox.left + hitbox.width, hitbox.top + hitbox.height));
        }
    }

    std::sort(points.begin(), points.end(), sortStruct);

    std::vector<point_t*> walls;

    for (point_t *point : points) {
        if (point->isStart) {
            walls.push_back(point);
        } else {
            walls.erase(std::remove(walls.begin(), walls.end(), point->pair));
        }
        std::cerr << "Walls in stack: " << walls.size() << std::endl;
//        sf::Vertex line[] = {
//            sf::Vertex(viewer->applyCameraTransformation(viewerPos), sf::Color::Red),
//            sf::Vertex(viewer->applyCameraTransformation(point.coords), sf::Color::Green)
//        };
//        window->draw(line, 2, sf::Lines);

        sortWallStruct.angle = point->angle;
        std::sort(walls.begin(), walls.end(), sortWallStruct);
    }

    std::cerr << "------------------" << std::endl;

    return result;
}

double VisibilityTracer::getAngle(sf::Vector2f origin, sf::Vector2f other) {
    float dx = other.x - origin.x;
    float dy = other.y - origin.y;
    return -atan2(dy, dx);
}
