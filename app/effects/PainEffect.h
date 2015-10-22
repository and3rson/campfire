//
// Created by anderson on 22.10.15.
//

#ifndef APP_PAINEFFECT_H
#define APP_PAINEFFECT_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "GameEngine.h"
#include "AEffect.h"

class Camera;

class PainEffect : public AEffect {

public:
    PainEffect(GameEngine *engine, Camera *camera, int power, int duration);

    virtual bool tick();

    sf::RenderWindow *window;

    int random(int max)
    {
#ifdef __linux__
        return ::random() % max;
#else
        return rand() % max;
#endif
    }

private:
    Camera *camera;
    sf::Clock clock;
    int power;
    int duration;
};


#endif //APP_PAINEFFECT_H
