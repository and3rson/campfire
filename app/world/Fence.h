//
// Created by anderson on 22.10.15.
//

#ifndef APP_FENCE_H
#define APP_FENCE_H


#include "Sprited.h"

class Fence : public Sprited {

public:
    Fence(Camera *camera);

    virtual void moveStarted();
    virtual void moveStopped();
};


#endif //APP_FENCE_H
