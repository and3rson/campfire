#ifndef CREATURE_H
#define CREATURE_H

#include "WorldObject.h"
#include "Movable.h"
#include "Sprited.h"
#include "Camera.h"

class Item;

class Creature : public Sprited
{
public:
    Creature(const char *, Camera *camera = 0);

    virtual void update();
    virtual void draw(sf::RenderWindow *window);

    virtual void moveStarted();
    virtual void moveStopped();

    virtual std::string getType();

    void arm(Item *item);
    void useArmedItem();
    WorldObject* dropArmedItem();
};

#endif // CREATURE_H
