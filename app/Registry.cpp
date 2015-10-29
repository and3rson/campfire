//
// Created by anderson on 27.10.15.
//

#include "Registry.h"
#include <iostream>

int Registry::refCount = 0;
std::vector<Registry *> Registry::allObjects;

Registry::Registry() {
}

void Registry::hold(Registry *object, const char *file, int line, const char *function) {
    std::cerr << file << ":" << line << ", in " << function << ": New object" << std::endl;

    this->objects.push_back(object);
    Registry::allObjects.push_back(object);
    Registry::refCount++;
//    this->printDebugInfo();
}

Registry::~Registry() {
    this->cleanUp();
}

void Registry::cleanUp() {
    std::cerr << "Cleaning up registry: " << this->objects.size() << " objects to delete" << std::endl;
    while (!this->objects.empty()) {
        Registry *objectToDelete = this->objects.back();
        for (std::vector<Registry *>::iterator it = Registry::allObjects.begin(); it != Registry::allObjects.end(); it++) {
            if ((*it) == objectToDelete) {
                Registry::allObjects.erase(it);
                break;
            }
        }

        delete objectToDelete;
        this->objects.pop_back();

        Registry::refCount--;
    }
}

int Registry::getRefCount() {
    return Registry::refCount;
}

std::vector<Registry *> Registry::getAllObjects() {
    return Registry::allObjects;
}
