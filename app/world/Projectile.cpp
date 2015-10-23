#include <GameEngine.h>
#include <effects/PainEffect.h>
#include "Projectile.h"

Projectile::Projectile(Camera *camera) : Sprited("bullet", camera)
{
    this->moveSpeed = 2000;
}

void Projectile::moveStarted()
{

}

void Projectile::moveStopped()
{

}

bool Projectile::collisionStarted(WorldObject *other) {
    std::cerr << "Object " << this->getType() << " collided with " << other->getType() << std::endl;
    this->parent->removeChild(this);
    if (other->getType() == "creature" && other->getIsCurrent()) {
        GameEngine::getInstance()->setEffect(new PainEffect(GameEngine::getInstance(), this->camera, 30, 400));
    }
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
    }
}
