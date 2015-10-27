//
// Created by anderson on 27.10.15.
//

#include "Registry.h"
#include <iostream>

int Registry::refCount = 0;

Registry::Registry() {
}

void Registry::hold(Registry *object, const char *file, int line, const char *function) {
    std::cerr << file << ":" << line << ", in " << function << ": New object" << std::endl;

    this->objects.push_back(object);
    Registry::refCount++;
    this->printDebugInfo();
}

Registry::~Registry() {
    this->cleanUp();
}

void Registry::cleanUp() {
    while (!this->objects.empty()) {
        delete this->objects.back();
        this->objects.pop_back();
        Registry::refCount--;
        this->printDebugInfo();
    }
}

void Registry::printDebugInfo() {
    std::cerr << "Objects in registry: " << Registry::refCount << std::endl;
}
