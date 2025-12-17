#ifndef CGM_VEC4_H
#define CGM_VEC4_H

/** 
 * @file vec4.h
 * mathematical operations for 4d vectors (float)
 * 
 * This file defines functions to work with 4D vectors including basic operations and vector algebra inspired by GLSL
 */

#include "util/core.h"
#include "ugm.h"
#include "structs/stcvec4.h"
#include <math.h>

/*
 * @brief create a 4d vector
 * @param x component x
 * @param y component y
 * @param z component z
 * @param w component w
 * @return vec4(x, y, z, w)
 * 
 */
CGMINLINE vec4 gmVec4(float x, float y, float z, float w)
{
    return (vec4){x, y, z, w};
}

/*
 * @brief add two vectors
 *
 */
CGMINLINE vec4 gmVec4add(vec4 v0, vec4 v1)
{
    float vx = v0.x + v1.x;
    float vy = v0.y + v1.y;
    float vz = v0.z + v1.z;
    float vw = v0.w + v1.w;
    return gmVec4(vx, vy, vz, vw);
}

#endif