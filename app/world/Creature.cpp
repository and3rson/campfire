#include "Creature.h"

Creature::Creature(Camera *camera) : Creature::Sprited("girl", camera)
{
}

void Creature::update()
{
    Sprited::update();
}

sf::Sprite Creature::getDrawable()
{
    return this->sprite;
}
