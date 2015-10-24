//
// Created by anderson on 09.10.15.
//

#include "Crate.h"
#include "Creature.h"

Crate::Crate(Camera *camera) : Item("crate", camera) {
    this->holdStyle = TWO_HANDED;
}

void Crate::use() {
//    this->projectile = new Projectile(this->camera);
//    projectile->setWPosition(sf::Vector2f(this->owner->wPosition));
//    projectile->wRotation = this->owner->wRotation;
//    projectile->startMove(sf::Vector2f(0, 1));
//    std::cerr << "SHOOT" << std::endl;
//    this->projectile = projectile;
}

void Crate::update() {
    Item::update();

//    if (this->projectile) {
//        this->projectile->update();
//    }
}

void Crate::draw(sf::RenderWindow *window) {
    Sprited::draw(window);

//    if (this->projectile) {
//        this->projectile->draw(window);
//    }
}

std::string Crate::getType() {
    return "crate";
}
