//
// Created by anderson on 09.10.15.
//

#ifndef APP_PISTOL_H
#define APP_PISTOL_H

#include "Item.h"
#include "Projectile.h"

class Pistol : public Item {

public:
    Pistol(Camera *camera);
    virtual void use();

    virtual void update();
    virtual void draw(sf::RenderWindow *window);

private:
    Projectile *projectile = 0;
};


#endif //APP_PISTOL_H
