#ifndef CGM_VEC2_H
#define CGM_VEC2_H

/** 
 * @file vec2.h
 * mathematical operations for 2d vectors (float)
 * 
 * This file defines functions to work with 2D vectors including basic operations and vector algebra inspired by GLSL
 */

#include "core.h"
#include "structs/stcvec2.h"
#include <math.h>

#define CGM_VEC2_ZERO ((vec2){0.0f, 0.0f}) /* vector(0) null */
#define CGM_VEC2_ONE  ((vec2){1.0f, 1.0f}) /* vector(1) unit */

/*
 * @brief create a 2d vector
 * @param x component x
 * @param y component y
 * @return vec2(x, y)
 * 
 */
CGMINLINE vec2 gmVec2(float x, float y)
{
    return (vec2){x, y};
}

/*
 * @brief negative vector
 * 
 */
CGMINLINE vec2 gmVec2neg(vec2 v)
{
    return gmVec2(-v.x, -v.y);
}

/*
 * @brief vector for a single value
 *
 * @return vec2(v, v) = vec2(1.0f)
 * 
 */
CGMINLINE vec2 gmVec2splat(float v)
{
    return gmVec2(v, v);
}

/*
 * @brief add two vectors
 *
 */
CGMINLINE vec2 gmVec2add(vec2 a1, vec2 a2)
{
    float x1 = a1.x + a2.x;
    float y1 = a1.y + a2.y;
    return gmVec2(x1, y1);
}

/*
 * @brief subtract two vectors
 *
 */
CGMINLINE vec2 gmVec2sub(vec2 a1, vec2 a2)
{
    float x1 = a1.x - a2.x;
    float y1 = a1.y - a2.y;
    return gmVec2(x1, y1);
}

/*
 * @brief multiply two vectors
 *
 */
CGMINLINE vec2 gmVec2mul(vec2 a1, vec2 a2)
{
    float x1 = a1.x * a2.x;
    float y1 = a1.y * a2.y;
    return gmVec2(x1, y1);
}

/*
 * @brief scale a vector by scalar
 *
 */
CGMINLINE vec2 gmVec2mulScale(vec2 v, float s)
{
    float x = v.x * s;
    float y = v.y * s;
    return gmVec2(x, y);
}

/*
 * @brief divide two vectors
 *
 */
CGMINLINE vec2 gmVec2div(vec2 v1, vec2 v2)
{
    float vx = v1.x / v2.x;
    float vy = v1.y / v2.y;
    return gmVec2(vx, vy);
}

/*
 * @brief Divide a vector by a scalar
 *
 */
CGMINLINE vec2 gmVec2divScale(vec2 v, float s)
{
    float vx = v.x / s;
    float vy = v.y / s;
    return gmVec2(vx, vy);
}

/*
 * @brief dot product between two vectors
 *
 */
CGMINLINE float gmVec2dot(vec2 v1, vec2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

/*
 * @brief length (magnitude) of the vector.
 *
 */
CGMINLINE float gmVec2length(vec2 g)
{
    return sqrtf(gmVec2dot(g, g));
}

/*
 * @brief normalize a vector
 *
 * @return normalized vector or `CGM_VEC2_ZERO` if length is 0.
 * 
 */
CGMINLINE vec2 gmVec2normalize(vec2 g)
{
    float length = gmVec2length(g);
    return (length == 0.0f) ?       CGM_VEC2_ZERO : 
    gmVec2divScale(g, length);
}

/*
 * @brief distance between two points
 *
 */
CGMINLINE float gmVec2distance(vec2 a, vec2 b)
{
    return gmVec2length(gmVec2sub(a, b));
}

/*
 * @brief reflects a vector with respect to a normal
 *
 * @param v incident vector
 * @param n normal
 * 
 * @note if `CGM_ASSUME_NORMALIZED` is 0,
 * normal is automatically normalized
 */
CGMINLINE vec2 gmVec2reflect(vec2 v, vec2 n)
{
#if !CGM_ASSUME_NORMALIZED
    n = gmVec2normalize(n);
#endif
    float d = gmVec2dot(v, n);
    return gmVec2sub(v, gmVec2mulScale(n, 2.0f * d));
}

/*
 * @brief calculates the refracted vector from an incident vector
 * 
 * @param v Incident vector
 * @param n surface normal
 * @param e refractive index (eta)
 * 
 * @note if `CGM_ASSUME_NORMALIZED` is 0,
 * normal is automatically normalized
 */
CGMINLINE vec2 gmVec2refract(vec2 v, vec2 n, float e)
{
#if !CGM_ASSUME_NORMALIZED
    n = gmVec2normalize(n);
#endif
    float d = gmVec2dot(n, v);
    float k = 1.0f - e * e * (1.0f - d * d);

    return (k < 0.0f) ? CGM_VEC2_ZERO : 
    gmVec2sub(
        gmVec2mulScale(v, e),
        gmVec2mulScale(n, e * d + sqrtf(k))
    );
}

/*
 * @brief applies floor to each component
 *
 */
CGMINLINE vec2 gmVec2floor(vec2 v)
{
    float fx = floorf(v.x);
    float fy = floorf(v.y);
    return gmVec2(fx, fy);
}

/*
 * @brief absolute value per component
 *
 */
CGMINLINE vec2 gmVec2abs(vec2 v)
{
    return gmVec2(fabsf(v.x), fabsf(v.y));
}

/*
 * @brief apply ceil to each component
 *
 */
CGMINLINE vec2 gmVec2ceil(vec2 v)
{
    return gmVec2(ceilf(v.x), ceilf(v.y));
}

/*
 * @brief fractional part of the vector
 * 
 * equivalent to `v - floor(v)`
 */
CGMINLINE vec2 gmVec2fract(vec2 v)
{
    float fx = gmFract(v.x);
    float fy = gmFract(v.y);
    return gmVec2(fx, fy);
}

/*
 * @brief minimum component to component
 * 
 */
CGMINLINE vec2 gmVec2min(vec2 a, vec2 b)
{
    return gmVec2(GMMIN(a.x, b.x), GMMIN(a.y, b.y));
}

/*
 * @brief maximum component to component
 *
 */
CGMINLINE vec2 gmVec2max(vec2 a, vec2 b)
{
    return gmVec2(GMMAX(a.x, b.x), GMMAX(a.y, b.y));
}

/*
 * @brief limits a vector between a minimum and a maximum
 *
 */
CGMINLINE vec2 gmVec2clamp(vec2 v, vec2 min, vec2 max)
{
    return gmVec2(
        gmClamp(v.x, min.x, max.x),
        gmClamp(v.y, min.y, max.y)
    );
}

/*
 * @brief linear interpolation between two vectors
 * 
 * @param a init vector
 * @param b final vector
 * @param t interpolation factor [0, 1]
 */
CGMINLINE vec2 gmVec2mix(vec2 a, vec2 b, float t)
{
    return gmVec2(
        gmMix(a.x, b.x, t),
        gmMix(a.y, b.y, t)
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
CGMINLINE vec2 gmVec2step(vec2 e, vec2 v)
{
    return gmVec2(
        gmStep(e.x, v.x),
        gmStep(e.y, v.y)
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
CGMINLINE vec2 gmVec2smoothstep(vec2 e0, vec2 e1, vec2 x)
{
    return gmVec2(
        gmSmoothstep(e0.x, e1.x, x.x),
        gmSmoothstep(e0.y, e1.y, x.y)
    );
}

CGMINLINE vec2 gmVec2fade(vec2 v)
{
    return gmVec2(
        gmFade(v.x),
        gmFade(v.y)
    );
}

#endif