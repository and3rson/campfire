//
// Created by anderson on 09.10.15.
//

#include "Pistol.h"
#include "Creature.h"

Pistol::Pistol(Camera *camera) : Item("pistol", camera) {
    this->holdStyle = ONE_HANDED;
    this->font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");
    this->updateAmmoGUI();
    if (!this->useSoundBuffer.loadFromFile("./res/sounds/pistol1.ogg")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    this->useSound.setBuffer(this->useSoundBuffer);
}

void Pistol::use() {
    if (this->ammo > 0) {
        Projectile *projectile = new Projectile(this->camera);
        // TODO: Move 12, -72 coordinates into JSON as some joint (e. g. "bullet_spawn_origin")
        projectile->setWPosition(
            sf::Vector2f(this->parent->getWPosition()) + this->rotateVector(sf::Vector2f(12, -72), this->parent->getWRotation()));
        projectile->setWRotation(this->parent->getWRotation());
        projectile->startMove(this->rotateVector(sf::Vector2f(0, -1), projectile->getWRotation()), false);
        this->addChild(projectile);

        this->useSound.play();

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
