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

#define CGM_VEC4_ZERO ((vec4){0.0f, 0.0f, 0.0f, 0.0f})
#define CGM_VEC4_ONE  ((vec4){1.0f, 1.0f, 1.0f, 1.0f})
#define CGM_VEC4_W    ((vec4){0.0f, 0.0f, 0.0f, 1.0f})

#define gmVec4xyz(v) ((vec3){(v).x, (v).y, (v).z})
#define gmVec4xy(v)  ((vec2){(v).x, (v).y})

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
 * @brief negative vector
 * 
 */
CGMINLINE vec4 gmVec4neg(vec4 v)
{
    return gmVec4(-v.x, -v.y, -v.z, -v.w);
}

/*
 * @brief vector for a single value
 *
 * @return vec4(v, v, v, v) = vec4(1.0f)
 * 
 */
CGMINLINE vec4 gmVec4splat(float v)
{
    return gmVec4(v, v, v, v);
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

/*
 * @brief subtract two vectors
 *
 */
CGMINLINE vec4 gmVec4sub(vec4 v0, vec4 v1)
{
    float vx = v0.x - v1.x;
    float vy = v0.y - v1.y;
    float vz = v0.z - v1.z;
    float vw = v0.w - v1.w;
    return gmVec4(vx, vy, vz, vw);
}

/*
 * @brief multiply two vectors
 *
 */
CGMINLINE vec4 gmVec4mul(vec4 v0, vec4 v1)
{
    float vx = v0.x * v1.x;
    float vy = v0.y * v1.y;
    float vz = v0.z * v1.z;
    float vw = v0.w * v1.w;
    return gmVec4(vx, vy, vz, vw);
}

/*
 * @brief scale a vector by scalar
 *
 */
CGMINLINE vec4 gmVec4mulScale(vec4 v, float s)
{
    float vx = v.x * s;
    float vy = v.y * s;
    float vz = v.z * s;
    float vw = v.w * s;
    return gmVec4(vx, vy, vz, vw);
}

/*
 * @brief divide two vectors
 *
 */
CGMINLINE vec4 gmVec4div(vec4 v0, vec4 v1)
{
    float vx = v0.x / v1.x;
    float vy = v0.y / v1.y;
    float vz = v0.z / v1.z;
    float vw = v0.w / v1.w;
    return gmVec4(vx, vy, vz, vw);
}

/*
 * @brief divide a vector by a scalar
 *
 */
CGMINLINE vec4 gmVec4divScale(vec4 v, float s)
{
    float vx = v.x / s;
    float vy = v.y / s;
    float vz = v.z / s;
    float vw = v.w / s;
    return gmVec4(vx, vy, vz, vw);
}

/*
 * @brief dot product between two vectors
 *
 */
CGMINLINE float gmVec4dot(vec4 v1, vec4 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

/*
 * @brief length (magnitude) of the vector.
 *
 */
CGMINLINE float gmVec4length(vec4 v)
{
    return sqrtf(gmVec4dot(v, v));
}

/*
 * @brief normalize a vector
 *
 * @return normalized vector or `CGM_VEC4_ZERO` if length is 0.
 * 
 */
CGMINLINE vec4 gmVec4normalize(vec4 v)
{
    float length = gmVec4length(v);
    return (length == 0.0f) ?       CGM_VEC4_ZERO :
    gmVec4divScale(v , length);
}

/*
 * @brief applies floor to each component
 *
 */
CGMINLINE vec4 gmVec4floor(vec4 v)
{
    float fx = floorf(v.x);
    float fy = floorf(v.y);
    float fz = floorf(v.z);
    float fw = floorf(v.w);
    return gmVec4(fx, fy, fz, fw);
}

/*
 * @brief absolute value per component
 *
 */
CGMINLINE vec4 gmVec4abs(vec4 v)
{
    return gmVec4(fabsf(v.x), fabsf(v.y), fabsf(v.z), fabsf(v.w));
}

/*
 * @brief apply ceil to each component
 *
 */
CGMINLINE vec4 gmVec4ceil(vec4 v)
{
    return gmVec4(ceilf(v.x), ceilf(v.y), ceilf(v.z), ceilf(v.w));
}

/*
 * @brief fractional part of the vector
 * 
 * equivalent to `v - floor(v)`
 */
CGMINLINE vec4 gmVec4fract(vec4 v)
{
    float fx = gmFract(v.x);
    float fy = gmFract(v.y);
    float fz = gmFract(v.z);
    float fw = gmFract(v.w);
    return gmVec4(fx, fy, fz, fw);
}

/*
 * @brief minimum component to component
 * 
 */
CGMINLINE vec4 gmVec4min(vec4 a, vec4 b)
{
    return gmVec4(GMMIN(a.x, b.x), GMMIN(a.y, b.y), GMMIN(a.z, b.z), GMMIN(a.w, b.w));
}

/*
 * @brief maximum component to component
 *
 */
CGMINLINE vec4 gmVec4max(vec4 a, vec4 b)
{
    return gmVec4(GMMAX(a.x, b.x), GMMAX(a.y, b.y), GMMAX(a.z, b.z), GMMAX(a.w, b.w));
}

/*
 * @brief limits a vector between a minimum and a maximum
 *
 */
CGMINLINE vec4 gmVec4clamp(vec4 v, vec4 min, vec4 max)
{
    return gmVec4(
        gmClamp(v.x, min.x, max.x),
        gmClamp(v.y, min.y, max.y),
        gmClamp(v.z, min.z, max.z),
        gmClamp(v.w, min.w, max.w)
    );
}

/*
 * @brief linear interpolation between two vectors
 * 
 * @param a init vector
 * @param b final vector
 * @param t interpolation factor [0, 1]
 */
CGMINLINE vec4 gmVec4mix(vec4 a, vec4 b, float t)
{
    return gmVec4(
        gmMix(a.x, b.x, t),
        gmMix(a.y, b.y, t),
        gmMix(a.z, b.z, t),
        gmMix(a.w, b.w, t)
    );
}

/*
 * @brief Returns 0.0 if x < edge, otherwise returns 1.0
 *
 * @param e threshold value
 * @param x input value
 *
 * @return 0.0 if x < edge, 1.0 otherwise
 */
CGMINLINE vec4 gmVec4step(vec4 e, vec4 v)
{
    return gmVec4(
        gmStep(e.x, v.x),
        gmStep(e.y, v.y),
        gmStep(e.z, v.z),
        gmStep(e.w, v.w)
    );
}

/*
 * @brief smooth Hermite interpolation between 0 and 1
 *
 * @param e0 lower edge of the transition
 * @param e1 upper edge of the transition
 * @param x input value
 *
 * @return
 *  0.0 if x <= e0
 *  1.0 if x >= e1
 */
CGMINLINE vec4 gmVec4smoothstep(vec4 e0, vec4 e1, vec4 x)
{
    return gmVec4(
        gmSmoothstep(e0.x, e1.x, x.x),
        gmSmoothstep(e0.y, e1.y, x.y),
        gmSmoothstep(e0.z, e1.z, x.z),
        gmSmoothstep(e0.w, e1.w, x.w)
    );
}

/**
 * @brief create a vec4 from a vec3 and a w component
 */
CGMINLINE vec4 gmVec4fromVec3(vec4 v, float w)
{
    return gmVec4(v.x, v.y, v.z, w);
}

#endif