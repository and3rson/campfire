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
#include "Recycler.h"

#include <X11/Xlib.h>

#undef None
#undef Status

#ifdef __linux__
#include <bits/stl_deque.h>
#include <bits/stl_queue.h>

#endif

#ifdef _WIN32
//#include <random>
#endif

using namespace std;

class GameEngine : public Registry
{
private:
    GameEngine(sf::RenderWindow *window);
public:
    virtual ~GameEngine();

    virtual std::string getType();

    static void initialize(sf::RenderWindow *window);
    static GameEngine* getInstance();
    void start();
    void tick();

    void setScene(AScene *);
    AScene *getScene();
    void setEffect(AEffect *);

    sf::RenderWindow *getWindow();

    GEEvent* getEvent();

    static void recycle(Registry *, const char *, int, const char *);

protected:
    static GameEngine* instance;
    sf::RenderWindow *window;

private:
    AScene *scene;
    AEffect *effect = 0;
    std::vector<GEEvent *> events;
    int lastX = -1, lastY = -1;

    static Recycler recycler;

#ifdef __linux__
    Display *dpy;
#endif
};

#endif // GAMEENGINE_H
