#ifndef ASCENE_H
#define ASCENE_H


class GameEngine;


class AScene
{
public:
    AScene(GameEngine *);

    virtual void tick() = 0;

protected:
    GameEngine *engine;
};

#endif // ASCENE_H
