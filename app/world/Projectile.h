#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Sprited.h"
#include "Camera.h"


class Projectile : public Sprited
{
public:
    Projectile(Camera *);

    void moveStarted();
    void moveStopped();

    virtual bool collisionStarted(WorldObject *other);
    virtual bool collisionStopped(WorldObject *other);
    virtual bool isCollidable();

    virtual std::string getType();
};

#endif // PROJECTILE_H
