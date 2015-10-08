#ifndef CREATURE_H
#define CREATURE_H

#include "WorldObject.h"
#include "Movable.h"
#include "Sprited.h"
#include "Camera.h"
#include "Item.h"


class Creature : public Sprited
{
public:
    Creature(const char *, Camera *camera = 0);

    void moveTo(sf::Vector2f);

    virtual void moveStarted();
    virtual void moveStopped();

private:
    Camera *camera = 0;
    Item *armedItem;
};

#endif // CREATURE_H
