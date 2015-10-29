//
// Created by anderson on 08.10.15.
//

#include <SoundManager.h>
#include "Item.h"
#include "Creature.h"

Item::Item(const char *definition, Camera *camera) : Sprited(definition, camera) {
    this->setAnimation("ground");

    SoundManager::getInstance()->load("arm_item");
}

void Item::update() {
    Sprited::update();

    if (this->parent) {
        this->setWPosition(this->parent->getWPosition());
        this->setWRotation(this->parent->getWRotation());
    }
}

std::string Item::getType() {
    return "item";
}

bool Item::isPickable() {
    return !this->parent;
}

void Item::armed() {
    SoundManager::getInstance()->play("arm_item");
}
