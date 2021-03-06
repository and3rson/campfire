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

    virtual void moveStarted() {};
    virtual void moveStopped() {};

    virtual void use() = 0;

    virtual std::string getType();

    virtual bool isPickable();

    enum EHoldStyle {
        ONE_HANDED,
        TWO_HANDED
    };

    EHoldStyle holdStyle = ONE_HANDED;

    virtual void armed();
};


#endif //APP_ITEM_H
