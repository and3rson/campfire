//
// Created by anderson on 29.10.15.
//
// Copyright 2000 softSurfer, 2012 Dan Sunday
// This code may be freely used, distributed and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.

#ifndef APP_WINDINGNUMBER_H
#define APP_WINDINGNUMBER_H


#include <SFML/System/Vector2.hpp>
#include "customtypes.h"

class WindingNumber {
public:
    static int wn_PnPoly(Point P, VectorList VN);
    static int cn_PnPoly(Point P, VectorList VN);
    static int isLeft(Point P0, Point P1, Point P2);
};


#endif //APP_WINDINGNUMBER_H
