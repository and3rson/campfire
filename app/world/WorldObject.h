#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <SFML/Graphics.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Camera;


class WorldObject
{
public:
    WorldObject(Camera *camera = 0);

    void update();
    void setPosition(sf::Vector2f);
    sf::Vector2f applyCameraTransformation(sf::Vector2f pos);

public:
    sf::Vector2f position;
    float rotation = 0;
    Camera *camera = 0;
};

#endif // WORLDOBJECT_H
