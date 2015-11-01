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
    ~Movable();
//    void moveTo(sf::Vector2f target);
    void startMove(sf::Vector2f vector, bool relative);
    void stopMove();

    virtual void moveStarted() = 0;
    virtual void moveStopped() = 0;

    virtual void update();
    virtual void draw(sf::RenderWindow *);

    sf::Vector2f getAccelerationVector();
    void setAccelerationVector(sf::Vector2f vector);

    sf::Vector2f getMomentumVector();
    void setMomentumVector(sf::Vector2f vector);

protected:
    int moveSpeed = 200;
    bool isMoving = false;
    float distanceTraveled = 0;

private:
    sf::Font font;

    sf::Vector2f source;
    sf::Vector2f target;
    sf::Clock clock;
//    sf::Vector2f *moveVector = 0;
    bool relative;

    float accelerationFactor = 8;

    sf::Vector2f momentumVector;
    sf::Vector2f accelerationVector;
};

#endif // MOVABLE_H
