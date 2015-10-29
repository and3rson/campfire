#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Registry.h>


class Animation : public Registry
{
public:
    Animation(const char *, const char *, int fps);
    virtual std::string getType();

    const char *getFullName();

    int fps;
    std::vector<sf::Vector2i> frames;
    char fullName[64];
};

#endif // ANIMATION_H
