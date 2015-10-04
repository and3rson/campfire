#include "Creature.h"

Creature::Creature(const char *templateName, Camera *camera) : Creature::Sprited(templateName, camera)
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

sf::RectangleShape Creature::getBoundsDrawable()
{
    static sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOrigin(this->sprite.getOrigin());
    rect.setPosition(this->sprite.getPosition());
    rect.setRotation(this->sprite.getRotation());
    rect.setSize(sf::Vector2f(this->sprite.getTextureRect().width, this->sprite.getTextureRect().height));
    return rect;
}
