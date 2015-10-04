#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "world/Camera.h"
#include "world/Creature.h"
#include "world/Grid.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

using namespace std;


class GameEngine
{
public:
    GameEngine(sf::RenderWindow *window);
    void start();
    void tick();

private:
    sf::RenderWindow *window;
    sf::View mapLayer;
    sf::View playerLayer;
    sf::View guiLayer;
    sf::Clock worldClock;
    sf::Clock frameClock;
    sf::Sprite sprite;
    Creature *player;
    Creature *enemy;
    Grid *grid;

    sf::Vector2i *lastMousePos;

    sf::Sprite groundSprite;

    Camera *camera;

    sf::Vector2f moveVector;

#ifdef __linux__
    Display *dpy;
    Window root_window;
#endif
};

#endif // GAMEENGINE_H
