#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>


class Animation
{
public:
    Animation(int fps);

    int fps;
    std::vector<sf::Vector2i> frames;
};

#endif // ANIMATION_H
