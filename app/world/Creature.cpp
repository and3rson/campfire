#include <GameEngine.h>
#include <effects/PainEffect.h>
#include "Creature.h"
#include "Item.h"

Creature::Creature(const char *templateName, Camera *camera) : Creature::Sprited(templateName, camera)
{
}

void Creature::moveStarted()
{
    if (this->children.size()) {
        switch (((Item *) this->children.front())->holdStyle) {
            case Item::ONE_HANDED:
                this->setAnimation("walk1");
                break;
            case Item::TWO_HANDED:
                // TODO: Implement this
                this->setAnimation("walk2");
                break;
        }
    } else {
        this->setAnimation("walk0");
    }
}

void Creature::moveStopped()
{
    if (this->children.size()) {
        switch (((Item *) this->children.front())->holdStyle) {
            case Item::ONE_HANDED:
                this->setAnimation("idle1");
                break;
            case Item::TWO_HANDED:
                this->setAnimation("idle2");
                // TODO: Implement this
                break;
        }
    } else {
        this->setAnimation("idle0");
    }
}

void Creature::update() {
    Sprited::update();
}

void Creature::draw(sf::RenderWindow *window) {
    Sprited::draw(window);
}

void Creature::arm(Item *item) {
    // TODO: Check if anything is armed already

    this->addChild(item);
    item->setAnimation("armed", true);
//    item->setPosition(sf::Vector2f(0, 0));
    this->moveStopped(); // TODO: Refactor setAnimation to allow suffixes.
}

void Creature::useArmedItem() {
    if (this->children.size()) {
        ((Item *) (this->children.front()))->use();
    }
}

std::string Creature::getType() {
    return "creature";
}

WorldObject* Creature::dropArmedItem() {
    if (this->children.size()) {
        WorldObject *dropped = this->children.front();
        dropped->setPosition(this->wPosition);
        ((Item *) dropped)->setAnimation("ground");
        this->removeChild(dropped);

        if (this->isMoving) {
            this->moveStarted();
        } else {
            this->moveStopped();
        }

//        this->moveStopped();

        return dropped;
    }
    return NULL;
}
