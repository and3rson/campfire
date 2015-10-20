//
// Created by anderson on 20.10.15.
//

#ifndef APP_DIRECTOR_H
#define APP_DIRECTOR_H

#include "duktape/duktape.h"


class Director {
public:
    static Director* getInstance();
private:
    Director();
    static Director *instance;
    duk_context *ctx;
};


#endif //APP_DIRECTOR_H
