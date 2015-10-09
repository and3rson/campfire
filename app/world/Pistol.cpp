//
// Created by anderson on 09.10.15.
//

#include "Pistol.h"

Pistol::Pistol(Camera *camera) : Item("pistol", camera) {
    this->holdStyle = ONE_HANDED;
}
