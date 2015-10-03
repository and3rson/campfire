#include "Creature.h"

Creature::Creature(Camera *camera) : Creature::Sprited("bob", camera)
{
}

void Creature::update()
{
    Sprited::update();
}

void Creature::moveTo(sf::Vector2f target)
{
    Sprited::moveTo(target);
}

void Creature::moveStarted()
{
    this->setAnimation("walk");
}

void Creature::moveStopped()
{
    this->setAnimation("idle");
}

sf::Sprite Creature::getDrawable()
{
    return this->sprite;
}
