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

//void Projectile::draw(sf::RenderWindow *window)
//{
//    Sprited::draw(window);
//}
