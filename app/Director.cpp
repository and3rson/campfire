//
// Created by anderson on 20.10.15.
//

#include <iostream>
#include "Director.h"

Director* Director::instance = 0;

Director::Director() {
    this->ctx = duk_create_heap_default();
    duk_eval_string(ctx, "print('Hello world!');");
    duk_destroy_heap(this->ctx);
}

Director *Director::getInstance() {
    if (!Director::instance) {
        Director::instance = new Director();
    }
    return Director::instance;
}
