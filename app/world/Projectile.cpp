#include "Projectile.h"

Projectile::Projectile(Camera *camera) : Sprited("bullet", camera)
{
    this->moveSpeed = 2000;
    SoundManager::getInstance()->load("hit_flesh");
    SoundManager::getInstance()->load("hit_wood");
    SoundManager::getInstance()->load("hit_concrete");
}

void Projectile::moveStarted()
{

}

void Projectile::moveStopped()
{

}

bool Projectile::collisionStarted(WorldObject *other) {
    // "other" may mot exist
    if (!other) {
        return false;
    }

    if (other->getType() == "projectile") {
        return false;
    }

    std::cerr << "Object " << this->getType() << " collided with " << other->getType() << std::endl;
    this->parent->removeChild(this);
    if (other->getType() == "creature" && other->getIsCurrent()) {
        GameEngine::getInstance()->setEffect(new PainEffect(GameEngine::getInstance(), this->camera, 30, 400));
    }

    switch (other->getMaterial()) {
        case NONE:break;
        case METAL:;break;
        case WOOD:
            SoundManager::getInstance()->play("hit_wood");
            break;
        case GLASS:break;
        case FLESH:
            char name[32];
            sprintf(name, "hit_flesh_%d", (int) this->randomMax(5) + 1);
            SoundManager::getInstance()->play(name);
            break;
        case CONCRETE:
            SoundManager::getInstance()->play("hit_concrete");
            break;
    }

    GameEngine::recycle(this, TRACE);
    return true;
}

bool Projectile::collisionStopped(WorldObject *other) {
    std::cerr << "Object " << this->getType() << " collides with " << other->getType() << " no more" << std::endl;
    return true;
}

bool Projectile::isCollidable() {
    return (bool) this->parent;
}

std::string Projectile::getType() {
    return "projectile";
}

void Projectile::update() {
    Sprited::update();

    if (this->distanceTraveled > 500) {
        this->parent->removeChild(this);
        GameEngine::recycle(this, TRACE);
    }
}

int Projectile::getDamage() {
    return 15;
}
