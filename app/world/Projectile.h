#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <GameEngine.h>
#include <effects/PainEffect.h>
#include "Sprited.h"
#include "Camera.h"
#include <SoundManager.h>

class Projectile : public Sprited
{
public:
    Projectile(Camera *);

    void moveStarted();
    void moveStopped();

    virtual bool collisionStarted(WorldObject *other);
    virtual bool collisionStopped(WorldObject *other);
    virtual bool isCollidable();

    virtual void update();

    virtual int getDamage();

    virtual std::string getType();
};

#endif // PROJECTILE_H
