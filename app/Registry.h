//
// Created by anderson on 27.10.15.
//

#ifndef APP_REGISTRY_H
#define APP_REGISTRY_H


#include <vector>
#include <iostream>

class Registry {
public:
    Registry();
    void hold(Registry *object, const char *, int, const char *);
    virtual ~Registry();

    void cleanUp();

    static int getRefCount();
    static std::vector<Registry *> getAllObjects();

    virtual std::string getType() = 0;

private:
    std::vector<Registry *> objects;
    static std::vector<Registry *> allObjects;
    static int refCount;
};


#endif //APP_REGISTRY_H
