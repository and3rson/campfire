#ifndef CAMERA_H
#define CAMERA_H

#include "Movable.h"

class WorldObject;


class Camera : public AMovable
{
public:
    Camera();
    void attachTo(WorldObject *target);
    virtual void update();

    virtual void moveStarted();
    virtual void moveStopped();
    virtual void draw(sf::RenderWindow *) {}

    virtual std::string getType();

    sf::Vector2f rShift;

private:
    WorldObject *target;
};

#endif // CAMERA_H
