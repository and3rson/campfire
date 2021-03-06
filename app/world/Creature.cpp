#include <GameEngine.h>
#include <effects/PainEffect.h>
#include "Creature.h"
#include "Item.h"
#include "Projectile.h"

Creature::Creature(const char *spriteName, Camera *camera) : Sprited(spriteName, camera) {

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
    item->armed();
//    item->setWPosition(sf::Vector2f(0, 0));
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
        dropped->setWPosition(this->getWPosition());
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

bool Creature::collisionStarted(WorldObject *other) {
    // "other" may mot exist
    if (!other) {
        return false;
    }

    if (other->getType() == "projectile") {
        this->health -= ((Projectile *) other)->getDamage();
    }

    if (this->health <= 0) {
        this->stopMove();
        this->setAnimation("idle2");
    }

    return true;
}

bool Creature::isAlive() {
    return this->health > 0;
}

Creature::~Creature() {
}

WorldObject::Material Creature::getMaterial() {
    return FLESH;
}
