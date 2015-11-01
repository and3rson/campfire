#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <SFML/Graphics.hpp>
#include <customtypes.h>

#include "../scenes/AScene.h"
#include "../world/Camera.h"
#include "world/Creature.h"
#include "world/Grid.h"
#include "world/Projectile.h"

class GameEngine;

class LevelScene : public AScene
{
public:
    LevelScene(GameEngine *);

    virtual void tick();
    WorldObjectList walk(WorldObject *object);

protected:
    void addObject(WorldObject *object);
//    void removeObject(WorldObject *object);

    void setControlledCreature(Creature *creature);
    Creature *getControlledCreature();
    void setActiveCamera(Camera *camera);
    Camera *getActiveCamera();

private:
    sf::Clock worldClock;
    sf::Clock frameClock;

    sf::RenderWindow *window;

    WorldObjectList objects;

    Creature *controlledCreature;
    Camera *activeCamera;

    int _dbgRandom()
    {
        #ifdef __linux__
        return random() % 100 + 100;
        #else
        return rand() % 100 + 100;
        #endif
    }

    sf::Font font;
};

#endif // MAINMENUSCENE_H
