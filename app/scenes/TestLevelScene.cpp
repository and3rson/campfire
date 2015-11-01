//
// Created by anderson on 30.10.15.
//

#include <world/Pistol.h>
#include <world/Fence.h>
#include <world/GenericEnemy.h>
#include <world/Crate.h>
#include <world/Bob.h>
#include "TestLevelScene.h"


TestLevelScene::TestLevelScene(GameEngine *engine) : LevelScene(engine) {
    this->setActiveCamera(new Camera());
    this->hold(this->getActiveCamera(), TRACE);
    this->hold(this->grid = new Grid(this->getActiveCamera()), TRACE);
    this->addObject(this->grid);

    this->hold(this->player = new Bob(this->getActiveCamera()), TRACE);
    this->player->setWPosition(sf::Vector2f(400, 300));
    Pistol *pistol1 = new Pistol(this->getActiveCamera());
    this->hold(pistol1, TRACE);
    this->player->arm(pistol1);
    this->player->setAsCurrent();
    this->addObject(this->player);
    this->setControlledCreature(this->player);

    Fence *fence = new Fence(this->getActiveCamera());
    this->hold(fence, TRACE);
    this->addObject(fence);

    Fence *fence2 = new Fence(this->getActiveCamera());
    this->hold(fence2, TRACE);
    fence2->setWPosition(sf::Vector2f(128, 0));
    this->addObject(fence2);

    this->hold(this->enemy = new GenericEnemy(this->getActiveCamera()), TRACE);
    this->enemy->setWPosition(sf::Vector2f(200, 200));
//    this->enemy->startMove(sf::Vector2f(0, -1), false);
    Pistol *pistol2 = new Pistol(this->getActiveCamera());
    this->hold(pistol2, TRACE);
    this->enemy->arm(pistol2);
    this->addObject(this->enemy);

    Crate *c1 = new Crate(this->getActiveCamera());
    c1->setWPosition(sf::Vector2f(300, 400));
    this->hold(c1, TRACE);
    this->addObject(c1);
    Crate *c2 = new Crate(this->getActiveCamera());
    c2->setWPosition(sf::Vector2f(200, 300));
    this->hold(c2, TRACE);
    this->addObject(c2);
    Crate *c3 = new Crate(this->getActiveCamera());
    c3->setWPosition(sf::Vector2f(300, 250));
    this->hold(c3, TRACE);
    this->addObject(c3);

    this->getActiveCamera()->attachTo(this->player);
}
