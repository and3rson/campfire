//
// Created by anderson on 09.10.15.
//

#ifndef APP_CRATE_H
#define APP_CRATE_H

#include "Item.h"

class Crate : public Item {

public:
    Crate(Camera *camera);
    virtual void use();

    virtual void update();
    virtual void draw(sf::RenderWindow *window);

//private:
//    Projectile *projectile = 0;
};


#endif //APP_CRATE_H
