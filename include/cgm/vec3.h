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

#define gmVec3xy(v) ((vec2){(v).x, (v).y})
#define gmVec3xz(v) ((vec2){(v).x, (v).z})
#define gmVec3yz(v) ((vec2){(v).y, (v).z})

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

/*
 * @brief distance between two points
 *
 */
CGMINLINE float gmVec3distance(vec3 a, vec3 b)
{
    return gmVec3length(gmVec3sub(a, b));
}

/*
 * @brief reflects a vector with respect to a normal
 *
 * @param v incident vector
 * @param n normal
 * 
 * @note if `CGM_AUTO_NORMALIZE` is defined,
 * normal is automatically normalized
 */
CGMINLINE vec3 gmVec3reflect(vec3 v, vec3 n)
{
#if CGM_AUTO_NORMALIZE
    n = gmVec3normalize(n);
#endif  
    float d = gmVec3dot(v, n);
    return gmVec3sub(v, gmVec3mulScale(n, 2.0f * d));
}

/*
 * @brief calculates the refracted vector from an incident vector
 * 
 * @param v Incident vector
 * @param n surface normal
 * @param e refractive index (eta)
 * 
 * @note if `CGM_AUTO_NORMALIZE` is defined,
 * normal is automatically normalized
 */
CGMINLINE vec3 gmVec3refract(vec3 v, vec3 n, float e)
{
#if CGM_AUTO_NORMALIZE
    n = gmVec3normalize(n);
#endif
    float d = gmVec3dot(n, v);
    float k = 1.0f - e * e * (1.0f - d * d);

    return (k < 0.0f) ? CGM_VEC3_ZERO :
    gmVec3sub(
        gmVec3mulScale(v, e),
        gmVec3mulScale(n, e * d + sqrtf(k))
    );
}

/*
 * @brief applies floor to each component
 *
 */
CGMINLINE vec3 gmVec3floor(vec3 v)
{
    float fx = floorf(v.x);
    float fy = floorf(v.y);
    float fz = floorf(v.z);
    return gmVec3(fx, fy, fz);
}

/*
 * @brief absolute value per component
 *
 */
CGMINLINE vec3 gmVec3abs(vec3 v)
{
    return gmVec3(fabsf(v.x), fabsf(v.y), fabsf(v.z));
}

/*
 * @brief apply ceil to each component
 *
 */
CGMINLINE vec3 gmVec3ceil(vec3 v)
{
    return gmVec3(ceilf(v.x), ceilf(v.y), ceilf(v.z));
}

/*
 * @brief fractional part of the vector
 * 
 * equivalent to `v - floor(v)`
 */
CGMINLINE vec3 gmVec3fract(vec3 v)
{
    float fx = gmFract(v.x);
    float fy = gmFract(v.y);
    float fz = gmFract(v.z);
    return gmVec3(fx, fy, fz);
}

/*
 * @brief minimum component to component
 * 
 */
CGMINLINE vec3 gmVec3min(vec3 a, vec3 b)
{
    return gmVec3(GMMIN(a.x, b.x), GMMIN(a.y, b.y), GMMIN(a.z, b.z));
}

/*
 * @brief maximum component to component
 *
 */
CGMINLINE vec3 gmVec3max(vec3 a, vec3 b)
{
    return gmVec3(GMMAX(a.x, b.x), GMMAX(a.y, b.y), GMMAX(a.z, b.z));
}

/*
 * @brief limits a vector between a minimum and a maximum
 *
 */
CGMINLINE vec3 gmVec3clamp(vec3 v, vec3 min, vec3 max)
{
    return gmVec3(
        gmClamp(v.x, min.x, max.x),
        gmClamp(v.y, min.y, max.y),
        gmClamp(v.z, min.z, max.z)
    );
}

/*
 * @brief linear interpolation between two vectors
 * 
 * @param a init vector
 * @param b final vector
 * @param t interpolation factor [0, 1]
 */
CGMINLINE vec3 gmVec3mix(vec3 a, vec3 b, float t)
{
    return gmVec3(
        gmMix(a.x, b.x, t),
        gmMix(a.y, b.y, t),
        gmMix(a.z, b.z, t)
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
CGMINLINE vec3 gmVec3step(vec3 e, vec3 v)
{
    return gmVec3(
        gmStep(e.x, v.x),
        gmStep(e.y, v.y),
        gmStep(e.z, v.z)
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
CGMINLINE vec3 gmVec3smoothstep(vec3 e0, vec3 e1, vec3 x)
{
    return gmVec3(
        gmSmoothstep(e0.x, e1.x, x.x),
        gmSmoothstep(e0.y, e1.y, x.y),
        gmSmoothstep(e0.z, e1.z, x.z)
    );
}

#endif