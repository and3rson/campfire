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
        sf::Vector2f coords;
        bool isStart;
        struct point_t *pair;
        double angle;

        point_t(sf::Vector2f _coords, double _angle) : coords(_coords), angle(_angle) {
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

//    struct wall_t {
//        sf::Vector2f start;
//        sf::Vector2f end;
////        double distance;
//        double angles[2];
//    };

    std::vector<point_t*> points;

    sf::Vector2f viewerPos = viewer->getWPosition();

    sf::Vector2f lines[] = {
        viewerPos - sf::Vector2f(-500, -500),
        viewerPos - sf::Vector2f(500, -500),
        viewerPos - sf::Vector2f(500, 500),
        viewerPos - sf::Vector2f(-500, 500)
    };

    for (int i = 0; i < 4; i++) {
        sf::Vector2f start = lines[i];
        sf::Vector2f end = lines[(i + 1) % 4];

        double angle1 = this->getAngle(viewerPos, start);
        double angle2 = this->getAngle(viewerPos, end);

        point_t *startPoint = new point_t(start, angle1);
        point_t *endPoint = new point_t(end, angle2);

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
            sf::Vertex(viewer->applyCameraTransformation(startPoint->coords), sf::Color::Red),
            sf::Vertex(viewer->applyCameraTransformation(endPoint->coords), sf::Color::Green)
        };
        window->draw(line, 2, sf::Lines);

//                walls.push_back(wall);
    }

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

                point_t *startPoint = new point_t(start, angle1);
                point_t *endPoint = new point_t(end, angle2);

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
                    sf::Vertex(viewer->applyCameraTransformation(startPoint->coords), sf::Color::Red),
                    sf::Vertex(viewer->applyCameraTransformation(endPoint->coords), sf::Color::Green)
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

    points.push_back(points.front());

//    std::vector<point_t*> walls;

    sf::Vector2f *first = 0;
    sf::Vector2f *last = 0;
    point_t *lastWall = 0;
    int i = -1;

    double lastAngle = -1;

    sf::Font font;
    font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");

    for (point_t *point : points) {
        float closestDistance;
        sf::Vector2f *closestIntersection;
        i++;

        for (int d = -1; d <= 1; d++) {
            if (d == -1 && i == 0) {
                continue;
            }
            if (d == 0) {
                closestDistance = WorldObject::getDistance(viewerPos, point->coords);
                closestIntersection = &(point->coords);
            } else {
                closestDistance = 0; // WorldObject::getDistance(viewerPos, point->coords);
                closestIntersection = NULL; //&(point->coords);
            }
            double angle = point->angle + ((double) d) / 100;
            if (angle > lastAngle) {
                sf::Vector2f projectionRay = viewerPos + WorldObject::rotateVector(sf::Vector2f(1000, 0), angle);

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
//                    if (d == -1) {
//                        color = sf::Color::Red;
//                    } else if (d == 0) {
//                        color = sf::Color::Green;
//                    } else {
//                        color = sf::Color::Blue;
//                    }
                    if (d == 1 && i == points.size() - 1) {
                        closestIntersection = first;
                    }
                    sf::ConvexShape shape;
                    shape.setPointCount(3);
                    shape.setPoint(0, viewer->applyCameraTransformation(viewerPos));
                    shape.setPoint(1, viewer->applyCameraTransformation(*last));
                    shape.setPoint(2, viewer->applyCameraTransformation(*closestIntersection));
                    shape.setFillColor(sf::Color(255, 255, 255, 32));
                    shape.setOutlineColor(sf::Color(255, 255, 255, 64));
                    shape.setOutlineThickness(1);
                    window->draw(shape);
//                    sf::Vertex line[] = {
//                        sf::Vertex(viewer->applyCameraTransformation(*last), color),
//                        sf::Vertex(viewer->applyCameraTransformation(*closestIntersection), color)
//                    };
//                    window->draw(line, 2, sf::Lines);
                }
                lastAngle = angle;
                last = closestIntersection;
            }
//            lastWall = wall;
        }
        points[0]->angle += M_PI * 2;
    }

    return result;
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
