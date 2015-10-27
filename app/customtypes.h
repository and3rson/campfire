//
// Created by anderson on 21.10.15.
//

#ifndef APP_CUSTOMTYPES_H
#define APP_CUSTOMTYPES_H

#include <vector>
class WorldObject;

typedef std::vector<WorldObject *> WorldObjectList;
typedef std::vector<sf::Vector2f> VectorList;

#define LOG(s, data...) log("%s:%s, in %s: "s, __FILE__, __LINE__,  __FUNCTION__, ## data)

#define TRACE __FILE__, __LINE__, __FUNCTION__

#endif //APP_CUSTOMTYPES_H
