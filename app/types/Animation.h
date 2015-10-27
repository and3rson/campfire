#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Registry.h>


class Animation : public Registry
{
public:
    Animation(int fps);

    int fps;
    std::vector<sf::Vector2i> frames;
};

#endif // ANIMATION_H
