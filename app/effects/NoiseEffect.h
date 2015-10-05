#ifndef NOISEEFFECT_H
#define NOISEEFFECT_H

#include "AEffect.h"
#include "GameEngine.h"

class NoiseEffect : public AEffect
{
public:
    NoiseEffect(GameEngine *);

    void tick();

    int random(int max)
    {
    #ifdef __linux__
        return ::random() % max;
    #else
        return rand() % max;
    #endif
    }

private:
    sf::RenderWindow *window;
};

#endif // NOISEEFFECT_H
