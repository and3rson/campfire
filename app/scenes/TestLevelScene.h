//
// Created by anderson on 30.10.15.
//

#ifndef APP_TESTLEVEL_H
#define APP_TESTLEVEL_H


#include "LevelScene.h"

class TestLevelScene : public LevelScene {

public:
    TestLevelScene(GameEngine *engine);

private:
    Creature *player;
    Creature *enemy;
    Grid *grid;
};


#endif //APP_TESTLEVEL_H
