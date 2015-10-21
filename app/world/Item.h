//
// Created by anderson on 08.10.15.
//

#ifndef APP_ITEM_H
#define APP_ITEM_H

#include "Sprited.h"

class Creature;

class Item : public Sprited {

public:
    Item(const char *definition, Camera *camera);

    virtual void update();
    void setOwner(Creature *owner);

    virtual void moveStarted() {};
    virtual void moveStopped() {};

    virtual void use() = 0;

    virtual std::string getType();

    enum EHoldStyle {
        ONE_HANDED,
        TWO_HANDED
    };

    EHoldStyle holdStyle = ONE_HANDED;
};


#endif //APP_ITEM_H
