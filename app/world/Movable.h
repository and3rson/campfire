#ifndef MOVABLE_H
#define MOVABLE_H

#include <math.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "WorldObject.h"

class Camera;


class AMovable : public WorldObject
{
public:
    AMovable(Camera *camera = 0);
    void moveTo(sf::Vector2f target);
    void startMove(sf::Vector2f vector, bool relative);
    void stopMove();

    virtual void moveStarted() = 0;
    virtual void moveStopped() = 0;

    virtual void update();

protected:
    int moveSpeed = 200;

    bool isMoving = false;
private:
    sf::Vector2f source;
    sf::Vector2f target;
    sf::Clock clock;
    sf::Vector2f *moveVector = 0;
    bool relative;
};

#endif // MOVABLE_H
