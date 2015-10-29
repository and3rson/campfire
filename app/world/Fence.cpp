//
// Created by anderson on 22.10.15.
//

#include "Fence.h"

Fence::Fence(Camera *camera) : Sprited("fence", camera) {

}

void Fence::moveStarted() {

}

void Fence::moveStopped() {

}

std::string Fence::getType() {
    return "Fence";
}

WorldObject::Material Fence::getMaterial() {
    return CONCRETE;
}
