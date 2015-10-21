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

    if (this->parent) {
        this->wPosition = this->parent->wPosition;
//        this->sprite.setPosition(this->applyCameraTransformation(this->parent->wPosition));
        this->wRotation = this->parent->wRotation;
    } else {
//        this->sprite.setPosition(this->applyCameraTransformation(this->wPosition));
//        this->wRotation = this->owner->wRotation;
    }
}

//void Item::setOwner(Creature *owner) {
//    this->parent = owner;
//
//    if (owner) {
//        this->setAnimation("armed", true);
//        std::cerr << "attached" << std::endl;
//    } else {
//        this->setAnimation("ground");
//        std::cerr << "detached" << std::endl;
//    };
//}

std::string Item::getType() {
    return "item";
}
