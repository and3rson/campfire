#ifndef SPLASHSCENE_H
#define SPLASHSCENE_H

#include "../GameEngine.h"
#include "AScene.h"

class SplashScene : public AScene
{
public:
    SplashScene(GameEngine *);

    virtual void tick();

private:
    sf::RenderWindow *window;
};

#endif // SPLASHSCENE_H
