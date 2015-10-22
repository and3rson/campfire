#ifndef AEFFECT_H
#define AEFFECT_H

class GameEngine;

class AEffect
{
public:
    AEffect(GameEngine *engine);
    virtual bool tick() = 0;

protected:
    GameEngine *engine;
};

#endif // AEFFECT_H
