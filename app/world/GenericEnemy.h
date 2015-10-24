//
// Created by anderson on 24.10.15.
//

#ifndef APP_GENERICENEMY_H
#define APP_GENERICENEMY_H


#include "Creature.h"

class Camera;

class GenericEnemy : public Creature {
public:
    GenericEnemy(Camera *camera);
};


#endif //APP_GENERICENEMY_H
