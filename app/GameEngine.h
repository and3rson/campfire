#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "scenes/AScene.h"
#include "effects/AEffect.h"
#include "Director.h"
#include "GEEvent.h"

#ifdef __linux__
#include <X11/Xlib.h>
#include <bits/stl_deque.h>
#include <bits/stl_queue.h>

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

    GEEvent* getEvent();

protected:
    sf::RenderWindow *window;

private:
    AScene *scene;
    AEffect *effect;
    std::vector<GEEvent *> events;
    int lastX = -1, lastY = -1;

#ifdef __linux__
    Display *dpy;
    Window root_window;
    int grab;
#endif
};

#endif // GAMEENGINE_H
