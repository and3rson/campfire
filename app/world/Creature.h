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
    Creature(const char *spriteName, Camera *camera);

    virtual void update();
    virtual void draw(sf::RenderWindow *window);

    virtual void moveStarted();
    virtual void moveStopped();

    virtual std::string getType();

    void arm(Item *item);
    void useArmedItem();
    WorldObject* dropArmedItem();

    virtual bool collisionStarted(WorldObject *other);

    bool isAlive();

protected:
    int health = 0;
    int maxHealth = 0;
};

#endif // CREATURE_H
