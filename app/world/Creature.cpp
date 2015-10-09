#include "Creature.h"
#include "Item.h"

Creature::Creature(const char *templateName, Camera *camera) : Creature::Sprited(templateName, camera)
{
}

void Creature::moveStarted()
{
    if (this->armedItem) {
        switch (this->armedItem->holdStyle) {
            case Item::ONE_HANDED:
                this->setAnimation("walk1");
                break;
            case Item::TWO_HANDED:
                // TODO: Implement this
                break;
        }
    } else {
        this->setAnimation("walk0");
    }
}

void Creature::moveStopped()
{
    if (this->armedItem) {
        switch (this->armedItem->holdStyle) {
            case Item::ONE_HANDED:
                this->setAnimation("idle1");
                break;
            case Item::TWO_HANDED:
                // TODO: Implement this
                break;
        }
    } else {
        this->setAnimation("idle0");
    }
}

void Creature::update() {
    Sprited::update();

    if (this->armedItem) {
        this->armedItem->update();
    }
}

void Creature::draw(sf::RenderWindow *window) {
    Sprited::draw(window);

    if (this->armedItem) {
        this->armedItem->draw(window);
    }
}

void Creature::arm(Item *item) {
    this->armedItem = item;
    this->armedItem->setOwner(this);
    this->moveStopped(); // TODO: Refactor setAnimation to allow suffixes.
}
