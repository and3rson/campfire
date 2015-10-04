#ifndef GRID_H
#define GRID_H


#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "WorldObject.h"

#define DENSITY 64


class Grid : public WorldObject
{
public:
    Grid(Camera *, sf::RenderWindow *);
    void draw();

private:
    sf::RenderWindow *window;
    sf::Font font;
};

#endif // GRID_H
