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
//    virtual void draw(sf::RenderWindow *window);
};

#endif // PROJECTILE_H
