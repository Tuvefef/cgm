#ifndef CGM_QUAT_H
#define CGM_QUAT_H

/**
 * @file quat.h
 */

#include "structs/stcquat.h"
#include "core.h"
#include "vec3.h"
#include <math.h>

#define CGM_QUAT_IDENTITY ((quat){0.0f, 0.0f, 0.0f, 1.0f})

/**
 * @brief creates a quaternion from components.
 *
 * @param x component x
 * @param y component y
 * @param z component z
 * @param w (scalar) component w
 */
CGMINLINE quat gmQuat(float x, float y, float z, float w)
{
    return (quat){x, y, z, w};
}

/**
 * @brief returns the identity quaternion.
 *
 * equivalent to no rotation.
 */
CGMINLINE quat gmQuatidentity(void)
{
    return CGM_QUAT_IDENTITY;
}

/**
 * @brief dot product between two quaternions.
 */
CGMINLINE float gmQuatdot(quat q0, quat q1)
{
    return q0.x * q1.x +
        q0.y * q1.y +
        q0.z * q1.z +
        q0.w * q1.w;
}

/**
 * @brief negates a quaternion.
 */
CGMINLINE quat gmQuatneg(quat q)
{
    return gmQuat(-q.x, -q.y, -q.z, -q.w);
}

/**
 * @brief multiplies two quaternions.
 * @param q0 left-hand quaternion
 * @param q1 right-hand quaternion
 */
CGMINLINE quat gmQuatmul(quat q0, quat q1)
{
    return gmQuat(
        q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y,
        q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x,
        q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w,
        q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z
    );
}

/**
 * @brief creates a quaternion from axis-angle representation.
 *
 * @param va rotation axis
 * @param a  rotation angle in radians
 *
 * @note if `CGM_ASSUME_NORMALIZED` is 0, the axis is normalized internally.
 */
CGMINLINE quat gmQuatAngle(vec3 va, float a)
{
#if !CGM_ASSUME_NORMALIZED
    va = gmVec3normalize(va);
#endif
    float h = a * 0.5f;
    float s = sinf(h);

    return gmQuat(
        va.x * s,
        va.y * s,
        va.z * s,
        cosf(h)
    );
}

#endif