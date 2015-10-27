#ifndef ASCENE_H
#define ASCENE_H


#include <Registry.h>

class GameEngine;


class AScene : public Registry
{
public:
    AScene(GameEngine *);

    virtual void tick() = 0;

protected:
    GameEngine *engine;
};

#endif // ASCENE_H
