//
// Created by anderson on 09.10.15.
//

#include "Pistol.h"
#include "Creature.h"

Pistol::Pistol(Camera *camera) : Item("pistol", camera) {
    this->holdStyle = ONE_HANDED;
}

void Pistol::use() {
    this->projectile = new Projectile(this->camera);
    projectile->setPosition(sf::Vector2f(this->owner->wPosition));
    projectile->wRotation = this->owner->wRotation;
    projectile->startMove(sf::Vector2f(0, 1));
    std::cerr << "SHOOT" << std::endl;
    this->projectile = projectile;
}

void Pistol::update() {
    Item::update();

    if (this->projectile) {
        this->projectile->update();
    }
}

void Pistol::draw(sf::RenderWindow *window) {
    Sprited::draw(window);

    if (this->projectile) {
        this->projectile->draw(window);
    }
}
