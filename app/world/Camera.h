#ifndef CAMERA_H
#define CAMERA_H

#include "Movable.h"

class WorldObject;


class Camera : public Movable
{
public:
    Camera();
    void attachTo(WorldObject *target);
    void update();

    virtual void moveStarted();
    virtual void moveStopped();

private:
    WorldObject *target;
};

#endif // CAMERA_H
