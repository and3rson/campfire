//
// Created by anderson on 24.10.15.
//

#include "GenericEnemy.h"

GenericEnemy::GenericEnemy(Camera *camera) : Creature("enemy", camera) {
    this->maxHealth = 100;
    this->health = this->maxHealth;
}
