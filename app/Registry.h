//
// Created by anderson on 27.10.15.
//

#ifndef APP_REGISTRY_H
#define APP_REGISTRY_H


#include <vector>

class Registry {
public:
    Registry();
    void hold(Registry *object, const char *, int, const char *);
    virtual ~Registry();

    void cleanUp();

    void printDebugInfo();

private:
    std::vector<Registry *> objects;
    static int refCount;
};


#endif //APP_REGISTRY_H
