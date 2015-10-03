#ifndef CREATURE_H
#define CREATURE_H

#include "WorldObject.h"
#include "Movable.h"
#include "Sprited.h"
#include "Camera.h"


class Creature : public Sprited
{
public:
    Creature(Camera *camera = 0);

    void update();
    void moveTo(sf::Vector2f);

    virtual void moveStarted();
    virtual void moveStopped();

    sf::Sprite getDrawable();

private:
    Camera *camera = 0;
};

#endif // CREATURE_H
