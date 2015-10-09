//
// Created by anderson on 08.10.15.
//

#include "Item.h"
#include "Creature.h"

Item::Item(const char *definition, Camera *camera) : Sprited(definition, camera) {

}

void Item::update() {
    Sprited::update();

    if (this->owner) {
        this->sprite.setPosition(this->applyCameraTransformation(this->owner->position));
        this->rotation = this->owner->rotation;
    } else {
    }
}

void Item::setOwner(Creature *owner) {
    this->owner = owner;

    if (owner) {
        this->setAnimation("armed", true);
        std::cerr << "ARMED";
    } else {
        this->setAnimation("ground");
    };
}
