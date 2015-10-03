#ifndef SPRITED_H
#define SPRITED_H

#include <fstream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <types/Animation.h>
//#include <json/reader.h>
#include <jsoncpp/json/json.h>

#include "Movable.h"
#include "Camera.h"


class Sprited : public Movable
{
public:
    Sprited(const char *, Camera *camera);
    void setAnimation(const char *);
    void update();

protected:
    sf::Texture texture;
    sf::Sprite sprite;

    int width;
    int height;

    std::map<std::string, Animation*> animations;

private:
    Animation *currentAnimation = 0;
    sf::Clock clock;
    int currentFrame = 0;
};

#endif // SPRITED_H
