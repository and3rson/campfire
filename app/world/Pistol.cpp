//
// Created by anderson on 09.10.15.
//

#include <SoundManager.h>
#include "Pistol.h"
#include "Creature.h"

Pistol::Pistol(Camera *camera) : Item("pistol", camera) {
    SoundManager::getInstance()->load("pistol3");
    SoundManager::getInstance()->load("arm_pistol");
//    SoundManager::getInstance()->load("drop_shell");

    this->holdStyle = ONE_HANDED;
    this->font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");
    this->updateAmmoGUI();
}

void Pistol::use() {
    if (timeSinceUsed.getElapsedTime().asMilliseconds() < 200) {
        return;
    }
    timeSinceUsed.restart();

    if (this->ammo > 0) {
        Projectile *projectile = new Projectile(this->camera);
        // TODO: Move 12, -72 coordinates into JSON as some joint (e. g. "bullet_spawn_origin")
        projectile->setWPosition(
            sf::Vector2f(this->parent->getWPosition()) + this->rotateVector(sf::Vector2f(12, -72), this->parent->getWRotation()));
        projectile->setWRotation(this->parent->getWRotation());
//        projectile->startMove(this->rotateVector(sf::Vector2f(0, -1), projectile->getWRotation()), false);
        sf::Vector2f shootVector = sf::Vector2f(0, -1);
        projectile->setAccelerationVector(shootVector);
        projectile->setMomentumVector(WorldObject::rotateVector(shootVector, this->getWRotation()));
        this->addChild(projectile);

        SoundManager::getInstance()->play("pistol3");
//        SoundManager::getInstance()->play("drop_shell");

        this->ammo--;
        this->updateAmmoGUI();
    } else {
        this->ammo = this->maxAmmo;
        this->updateAmmoGUI();
    }
}

void Pistol::update() {
    Item::update();

//    if (this->projectile) {
//        this->projectile->update();
//    }
}

void Pistol::draw(sf::RenderWindow *window) {
    Sprited::draw(window);

    if (this->parent && this->parent->getIsCurrent()) {
        window->draw(this->ammoText);
    }
}

std::string Pistol::getType() {
    return "pistol";
}

bool Pistol::isCollidable() {
    return false;
}

void Pistol::updateAmmoGUI() {
    char text[32];
    sprintf(text, "%d/%d", this->ammo, this->maxAmmo);
    this->ammoText = sf::Text(sf::String(text), this->font, 24);
    this->ammoText.setPosition(10, 10);
}

void Pistol::armed() {
    SoundManager::getInstance()->play("arm_pistol");
}
