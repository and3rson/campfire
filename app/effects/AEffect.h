#ifndef AEFFECT_H
#define AEFFECT_H

#include <Registry.h>

class GameEngine;

class AEffect : public Registry
{
public:
    AEffect(GameEngine *engine);
    virtual bool tick() = 0;

protected:
    GameEngine *engine;
};

#endif // AEFFECT_H
