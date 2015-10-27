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

class MainMenuScene : public AScene
{
public:
    MainMenuScene(GameEngine *);
    virtual void tick();
    WorldObjectList walk(WorldObject *object);

private:
    sf::Clock worldClock;
    sf::Clock frameClock;

    sf::Sprite sprite;
    Creature *player;
    Creature *enemy;
    Grid *grid;

    Camera *camera;

    sf::Vector2f moveVector;

    sf::RenderWindow *window;

    WorldObjectList objects;

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
