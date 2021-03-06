//
// Created by anderson on 29.10.15.
//

#include "WindingNumber.h"

// Copyright 2000 softSurfer, 2012 Dan Sunday
// This code may be freely used, distributed and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.


// isLeft(): tests if a point is Left|On|Right of an infinite line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2  on the line
//            <0 for P2  right of the line
//    See: Algorithm 1 "Area of Triangles and Polygons"
int WindingNumber::isLeft(Point P0, Point P1, Point P2) {
    return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}
//===================================================================


// cn_PnPoly(): crossing number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  0 = outside, 1 = inside
// This code is patterned after [Franklin, 2000]
int WindingNumber::cn_PnPoly(Point P, VectorList VL) {
    int cn = 0;    // the  crossing number counter

    Point V[VL.size()];
    int c = 0;
    for (Point p : VL) {
        V[c++] = p;
    }

    // loop through all edges of the polygon
    for (int i = 0; i < VL.size(); i++) {    // edge from V[i]  to V[i+1]
        if (((V[i].y <= P.y) && (V[i + 1].y > P.y))     // an upward crossing
            || ((V[i].y > P.y) && (V[i + 1].y <= P.y))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float) (P.y - V[i].y) / (V[i + 1].y - V[i].y);
            if (P.x < V[i].x + vt * (V[i + 1].x - V[i].x)) // P.x < intersect
                ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }
    return (cn & 1);    // 0 if even (out), and 1 if  odd (in)

}
//===================================================================


// wn_PnPoly(): winding number test for a point in a polygon
//      Input:   P = a point,
//               V[] = vertex points of a polygon V[n+1] with V[n]=V[0]
//      Return:  wn = the winding number (=0 only when P is outside)
int WindingNumber::wn_PnPoly(Point P, VectorList VL) {
    int wn = 0;    // the  winding number counter

    Point V[VL.size()];
    int c = 0;
    for (Point p : VL) {
        V[c++] = p;
    }

    // loop through all edges of the polygon
    for (int i = 0; i < VL.size(); i++) {   // edge from V[i] to  V[i+1]
        if (V[i].y <= P.y) {          // start y <= P.y
            if (V[i + 1].y > P.y)      // an upward crossing
            if (isLeft(V[i], V[i + 1], P) > 0)  // P left of  edge
                ++wn;            // have  a valid up intersect
        } else {                        // start y > P.y (no test needed)
            if (V[i + 1].y <= P.y)     // a downward crossing
            if (isLeft(V[i], V[i + 1], P) < 0)  // P right of  edge
                --wn;            // have  a valid down intersect
        }
    }
    return wn;
}
//===================================================================
int WindingNumber::insidePolygon(VectorList vectors, Point p) {
    int counter = 0;
    int i;
    double xinters;
    Point p1, p2;

    unsigned long n = vectors.size();

    Point polygon[n];

    int k = 0;
    for(Point vector : vectors) {
        polygon[k] = vector;
    }

    p1 = polygon[0];
    for (i = 1; i <= n; i++) {
        p2 = polygon[i % n];
        if (p.y > MIN(p1.y, p2.y)) {
            if (p.y <= MAX(p1.y, p2.y)) {
                if (p.x <= MAX(p1.x, p2.x)) {
                    if (p1.y != p2.y) {
                        xinters = (p.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
                        if (p1.x == p2.x || p.x <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    if (counter % 2 == 0)
        return (OUTSIDE);
    else
        return (INSIDE);
}
