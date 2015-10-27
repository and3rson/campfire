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
    struct {
        sf::Vector2f viewerPos;

        double getAngle(sf::Vector2f origin, sf::Vector2f other) {
            float dx = other.x - origin.x;
            float dy = other.y - origin.y;
            float result = atan2(dy, dx);
            if (result < 0) {
                result += M_PI * 2;
            }
            return result;
        }

        bool operator() (point_t *a, point_t *b) {
            return getAngle(viewerPos, a->coords) < getAngle(viewerPos, b->coords);
        }
    } sortStruct;

    sortStruct.viewerPos = viewer->getWPosition();

    std::vector<point_t*> points;

    sf::Vector2f viewerPos = viewer->getWPosition();

    sf::Vector2u size = window->getSize();
    int hypotenuse = (int) sqrt(pow(size.x / 2, 2) + pow(size.y / 2, 2));

    sf::Vector2f lines[] = {
        viewerPos + sf::Vector2f(- hypotenuse, - hypotenuse),
        viewerPos + sf::Vector2f(+ hypotenuse, - hypotenuse),
        viewerPos + sf::Vector2f(+ hypotenuse, + hypotenuse),
        viewerPos + sf::Vector2f(- hypotenuse, + hypotenuse)
    };

    for (int i = 0; i < 4; i++) {
        sf::Vector2f start = lines[i];
        sf::Vector2f end = lines[(i + 1) % 4];

        double angle1 = this->getAngle(viewerPos, start);
        double angle2 = this->getAngle(viewerPos, end);

        point_t *startPoint = new point_t(start, angle1);
        point_t *endPoint = new point_t(end, angle2);

        startPoint->pair = endPoint;
        endPoint->pair = startPoint;

        points.push_back(startPoint);
        points.push_back(endPoint);

//        sf::Vertex line[] = {
//            sf::Vertex(viewer->applyCameraTransformation(startPoint->coords), sf::Color::Red),
//            sf::Vertex(viewer->applyCameraTransformation(endPoint->coords), sf::Color::Green)
//        };
//        window->draw(line, 2, sf::Lines);

//                walls.push_back(wall);
    }

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

                point_t *startPoint = new point_t(start, angle1);
                point_t *endPoint = new point_t(end, angle2);

                startPoint->pair = endPoint;
                endPoint->pair = startPoint;

                points.push_back(startPoint);
                points.push_back(endPoint);

//                sf::Vertex line[] = {
//                    sf::Vertex(viewer->applyCameraTransformation(startPoint->coords), sf::Color::Red),
//                    sf::Vertex(viewer->applyCameraTransformation(endPoint->coords), sf::Color::Green)
//                };
//                window->draw(line, 2, sf::Lines);
            }
        }
    }

    std::sort(points.begin(), points.end(), sortStruct);

    points.push_back(points.front());

//    std::vector<point_t*> walls;

    sf::Vector2f *first = 0;
    sf::Vector2f *last = 0;
    point_t *lastWall = 0;
    int i = -1;
    int tracedCount = 0;

    double lastAngle = -1;

    VectorList visionPoly;

    for (point_t *point : points) {
        float closestDistance;
        sf::Vector2f *closestIntersection;

        for (int d = -1; d <= 1; d++) {
            i++;
            if (d == -1 && i == 0) {
                continue;
            }
            if (d == 0) {
                closestDistance = WorldObject::getDistance(viewerPos, point->coords);
                closestIntersection = &(point->coords);
            } else {
                closestDistance = 0;
                closestIntersection = NULL;
            }
            double angle = point->angle + ((double) d) / 1000;
            if (angle > lastAngle) {
                sf::Vector2f projectionRay = viewerPos + WorldObject::rotateVector(sf::Vector2f(3000, 0), angle);

                for (point_t *other : points) {
                    sf::Vector2f *intersection = this->getIntersection(viewerPos, projectionRay, other->coords,
                                                                       other->pair->coords);
                    if (intersection) {
                        float distance = WorldObject::getDistance(viewerPos, *intersection);
                        if (distance < closestDistance || !closestIntersection) {
                            closestIntersection = intersection;
                            closestDistance = distance;
                        } else {
                            delete intersection;
                        }
                    }
                }
                if (!first) {
                    first = closestIntersection;
                }
                if (last) {
                    sf::Color color = sf::Color::White;
                    if (d == 1 && i == points.size() - 1) {
                        closestIntersection = first;
                    }
                    if (closestIntersection) {
                        tracedCount++;
                        visionPoly.push_back(*closestIntersection);
                    }
                }
                lastAngle = angle;
                last = closestIntersection;
            }
        }
        points[0]->angle += M_PI * 2;
    }

    points.pop_back();

    while (!points.empty()) {
        delete points.back();
        points.pop_back();
    }

    return visionPoly;
}

double VisibilityTracer::getAngle(sf::Vector2f origin, sf::Vector2f other) {
    float dx = other.x - origin.x;
    float dy = other.y - origin.y;
    float result = atan2(dy, dx);
    if (result < 0) {
        result += M_PI * 2;
    }
    return result;
}

sf::Vector2f *VisibilityTracer::getIntersection(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
    double s1_x = p1.x - p0.x;
    double s1_y = p1.y - p0.y;
    double s2_x = p3.x - p2.x;
    double s2_y = p3.y - p2.y;

//                if(p0.isSame(p2) || p0.isSame(p3)) {
//                    return p0;
//                }
//
//                if(p1.isSame(p2) || p1.isSame(p3)) {
//                    return p1;
//                }

    double s = (-s1_y * (p0.x - p2.x) + s1_x * (p0.y - p2.y)) / (-s2_x * s1_y + s1_x * s2_y);
    double t = ( s2_x * (p0.y - p2.y) - s2_y * (p0.x - p2.x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected
        double i_x = p0.x + (t * s1_x);
        double i_y = p0.y + (t * s1_y);
        return new sf::Vector2f(i_x, i_y);
    }
    return NULL;
}
