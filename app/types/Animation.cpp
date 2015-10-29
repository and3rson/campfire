#include "Animation.h"

Animation::Animation(const char *spriteName, const char *animationName, int fps) : fps(fps)
{
    sprintf(this->fullName, "%s:%s", spriteName, animationName);
}

std::string Animation::getType() {
    return "animation";
}

const char *Animation::getFullName() {
    return this->fullName;
}
