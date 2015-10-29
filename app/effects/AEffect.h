#ifndef AEFFECT_H
#define AEFFECT_H

#include <Registry.h>

class GameEngine;

class AEffect : public Registry
{
public:
    AEffect(GameEngine *engine);
    virtual bool tick() = 0;
    virtual std::string getType();

protected:
    GameEngine *engine;
};

#endif // AEFFECT_H
