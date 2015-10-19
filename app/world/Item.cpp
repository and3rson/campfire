//
// Created by anderson on 08.10.15.
//

#include "Item.h"
#include "Creature.h"

Item::Item(const char *definition, Camera *camera) : Sprited(definition, camera) {
    this->setAnimation("ground");
}

void Item::update() {
    Sprited::update();

    if (this->owner) {
        this->sprite.setPosition(this->applyCameraTransformation(this->owner->wPosition));
        this->wRotation = this->owner->wRotation;
    } else {
        this->sprite.setPosition(this->applyCameraTransformation(this->wPosition));
//        this->wRotation = this->owner->wRotation;
    }
}

void Item::setOwner(Creature *owner) {
    this->owner = owner;

    if (owner) {
        this->setAnimation("armed", true);
        std::cerr << "attached" << std::endl;
    } else {
        this->setAnimation("ground");
        std::cerr << "detached" << std::endl;
    };
}

std::string Item::getType() {
    return "item";
}
