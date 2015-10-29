#include "AScene.h"
#include "GameEngine.h"

AScene::AScene(GameEngine *engine) : engine(engine)
{

}

std::string AScene::getType() {
    return "AScene";
}
