//
// Created by anderson on 24.10.15.
//

#include "Bob.h"

Bob::Bob(Camera *camera) : Creature("bob", camera) {
    this->maxHealth = 100;
    this->health = this->maxHealth;
}
