#include "Creature.h"

Creature::Creature(const char *templateName, Camera *camera) : Creature::Sprited(templateName, camera)
{
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
