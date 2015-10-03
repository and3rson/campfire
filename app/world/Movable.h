#ifndef MOVABLE_H
#define MOVABLE_H

#include <math.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "WorldObject.h"

class Camera;


class Movable : public WorldObject
{
public:
    Movable(Camera *camera = 0);
    void moveTo(sf::Vector2f target);
    void startMove(sf::Vector2f vector);
    void stopMove();

    void update();

protected:
    int moveSpeed = 100;

private:
    sf::Vector2f source;
    sf::Vector2f target;
    sf::Clock clock;
    sf::Vector2f *moveVector = 0;
    bool isMoving = false;
};

#endif // MOVABLE_H
