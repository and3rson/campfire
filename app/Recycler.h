//
// Created by anderson on 29.10.15.
//

#ifndef APP_RECYCLER_H
#define APP_RECYCLER_H


#include "Registry.h"

class Recycler : public Registry {
    virtual std::string getType();
};


#endif //APP_RECYCLER_H
