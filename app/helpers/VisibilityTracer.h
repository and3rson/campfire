//
// Created by anderson on 26.10.15.
//

#ifndef APP_VISIBILITYTRACER_H
#define APP_VISIBILITYTRACER_H

#include "customtypes.h"

class VisibilityTracer {
public:
    VisibilityTracer(WorldObjectList objects);

    VectorList calculateVisibility(WorldObject *viewer);

private:
    WorldObjectList objects;
};


#endif //APP_VISIBILITYTRACER_H
