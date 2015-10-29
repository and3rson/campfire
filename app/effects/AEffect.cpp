#include "AEffect.h"

AEffect::AEffect(GameEngine *engine) : engine(engine)
{

}

std::string AEffect::getType() {
    return "AEffect";
}
