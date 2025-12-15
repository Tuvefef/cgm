#ifndef CGM_VEC3_H
#define CGM_VEC3_H

/** 
 * @file vec3.h
 * mathematical operations for 3d vectors (float)
 * 
 * This file defines functions to work with 3D vectors including basic operations and vector algebra inspired by GLSL
 */

#include "util/core.h"
#include "ugm.h"
#include "structs/stcvec3.h"
#include <math.h>

#define CGM_VEC3_ZERO ((vec3){0.0f, 0.0f, 0.0f})
#define CGM_VEC3_ONE  ((vec3){1.0f, 1.0f, 1.0f})

/*
 * @brief create a 3d vector
 * @param x component x
 * @param y component y
 * @param z component z
 * @return vec3(x, y, z)
 * 
 */

CGMINLINE vec3 gmVec3(float x, float y, float z)
{
    return (vec3){x, y, z};
}

/*
 * @brief negative vector
 * 
 */
CGMINLINE vec3 gmVec3neg(vec3 v)
{
    return gmVec3(-v.x, -v.y, -v.z);
}

/*
 * @brief vector for a single value
 *
 * @return vec3(v, v, v) = vec3(1.0f)
 * 
 */
CGMINLINE vec3 gmVec3splat(float v)
{
    return gmVec3(v, v, v);
}

/*
 * @brief add two vectors
 *
 */
CGMINLINE vec3 gmVec3add(vec3 v1, vec3 v2)
{
    float vx = v1.x + v2.x;
    float vy = v1.y + v2.y;
    float vz = v1.z + v2.z;
    return gmVec3(vx, vy, vz);
}

/*
 * @brief subtract two vectors
 *
 */
CGMINLINE vec3 gmVec3sub(vec3 v1, vec3 v2)
{
    float vx = v1.x - v2.x;
    float vy = v1.y - v2.y;
    float vz = v1.z - v2.z;
    return gmVec3(vx, vy, vz);
}

/*
 * @brief multiply two vectors
 *
 */
CGMINLINE vec3 gmVec3mul(vec3 v1, vec3 v2)
{
    float vx = v1.x * v2.x;
    float vy = v1.y * v2.y;
    float vz = v1.z * v2.z;
    return gmVec3(vx, vy, vz);
}

/*
 * @brief scale a vector by scalar
 *
 */
CGMINLINE vec3 gmVec3mulScale(vec3 v, float s)
{
    float sx = v.x * s;
    float sy = v.y * s;
    float sz = v.z * s;
    return gmVec3(sx, sy, sz);
}

/*
 * @brief divide two vectors
 *
 */
CGMINLINE vec3 gmVec3div(vec3 v1, vec3 v2)
{
    float vx = v1.x / v2.x;
    float vy = v1.y / v2.y;
    float vz = v1.z / v2.z;
    return gmVec3(vx, vy, vz);
}

/*
 * @brief divide a vector by a scalar
 *
 */
CGMINLINE vec3 gmVec3divScale(vec3 v, float s)
{
    float sx = v.x / s;
    float sy = v.y / s;
    float sz = v.z / s;
    return gmVec3(sx, sy, sz);
}

/*
 * @brief dot product between two vectors
 *
 */
CGMINLINE float gmVec3dot(vec3 v1, vec3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
}

/*
 * @brief length (magnitude) of the vector.
 *
 */
CGMINLINE float gmVec3length(vec3 v)
{
    return sqrtf(gmVec3dot(v, v));
}

/*
 * @brief normalize a vector
 *
 * @return normalized vector or `CGM_VEC3_ZERO` if length is 0.
 * 
 */
CGMINLINE vec3 gmVec3normalize(vec3 v)
{
    float length = gmVec3length(v);
    return (length == 0.0f) ?       CGM_VEC3_ZERO :
    gmVec3divScale(v, length);
}

/*
 * @brief compute cross product of two 3D vectors
 * @param v1 first input vector
 * @param v2 second input vector
 * @return a vector perpendicular to v1 and v2
 */
CGMINLINE vec3 gmVec3cross(vec3 v1, vec3 v2)
{
    float i = v1.y * v2.z - v1.z * v2.y;
    float j = v1.z * v2.x - v1.x * v2.z;
    float k = v1.x * v2.y - v1.y * v2.x;
    return gmVec3(i, j, k);
}

#endif