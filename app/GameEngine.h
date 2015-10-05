#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "scenes/AScene.h"
#include "effects/AEffect.h"

#ifdef __linux__
#include <X11/Xlib.h>
#endif

#ifdef _WIN32
//#include <random>
#endif

using namespace std;


class GameEngine
{
public:
    GameEngine(sf::RenderWindow *window);
    void start();
    void tick();

    void setScene(AScene *);
    void setEffect(AEffect *);

    sf::RenderWindow *getWindow();

protected:
    sf::RenderWindow *window;

private:
    AScene *scene;
    AEffect *effect;

#ifdef __linux__
    Display *dpy;
    Window root_window;
#endif
};

#endif // GAMEENGINE_H
