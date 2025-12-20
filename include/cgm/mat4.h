#ifndef CGM_MAT4_H
#define CGM_MAT4_H

/**
 * @file mat4.h
 * 
 */

#include "util/core.h"
#include "ugm.h"
#include "structs/stcmat4.h"
#include <math.h>

#define CGM_MAT4_INIT ((mat4){0})

/**
 * @brief create an identity matrix
 */
CGMINLINE mat4 gmMat4identity(void)
{
    mat4 m = CGM_MAT4_INIT;
    m.m[0]  = 1.0f;
    m.m[5]  = 1.0f;
    m.m[10] = 1.0f;
    m.m[15] = 1.0f;
    return m;
}

/**
 * @brief multiplication of two mat4 (m0 * m1)
 */
CGMINLINE mat4 gmMat4mul(mat4 m0, mat4 m1)
{
    mat4 m = CGM_MAT4_INIT;
    for(int c0 = 0; c0 < 4; c0++)
    {
        for(int r0 = 0; r0 < 4; r0++)
        {
            m.m[c0 * 4 + r0] =
                m0.m[0 * 4 + r0] * m1.m[c0 * 4 + 0] +
                m0.m[1 * 4 + r0] * m1.m[c0 * 4 + 1] +
                m0.m[2 * 4 + r0] * m1.m[c0 * 4 + 2] +
                m0.m[3 * 4 + r0] * m1.m[c0 * 4 + 3];
        }
    }
    return m;
}

/**
 * @brief translation matrix
 * @param x translation x
 * @param y translation y
 * @param z translation z
 */
CGMINLINE mat4 gmMat4translate(float x, float y, float z)
{
    mat4 m = gmMat4identity();
    m.m[12] = x;
    m.m[13] = y;
    m.m[14] = z;
    return m;
}

/**
 * @brief scaling matrix (column major)
 * @param x scale on axis x
 * @param y scale on axis y
 * @param z scale on axis z
 */
CGMINLINE mat4 gmMat4scale(float x, float y, float z)
{
    mat4 m = gmMat4identity();
    m.m[0] = x;
    m.m[5] = y;
    m.m[10] = z;
    return m;
}

/**
 * @brief x axis rotation matrix
 * @param ma angle in radians
 */
CGMINLINE mat4 gmMat4Xrotate(float ma)
{
    mat4 m = gmMat4identity();
    m.m[5] =  cosf(ma);
    m.m[6] = -sinf(ma);
    m.m[9] =  sinf(ma);
    m.m[10] = cosf(ma);
    return m;
}

/**
 * @brief y axis rotation matrix
 * @param ma angle in radians
 */
CGMINLINE mat4 gmMat4Yrotate(float ma)
{
    mat4 m = gmMat4identity();
    m.m[0] =  cosf(ma);
    m.m[2] = -sinf(ma);
    m.m[8] =  sinf(ma);
    m.m[10] = cosf(ma);
    return m;
}


/**
 * @brief z axis rotation matrix
 * @param ma angle in radians
 */
CGMINLINE mat4 gmMat4Zrotate(float ma)
{
    mat4 m = gmMat4identity();
    m.m[0] =  cosf(ma);
    m.m[4] = -sinf(ma);
    m.m[1] =  sinf(ma);
    m.m[5] =  cosf(ma);
    return m;
}

/**
 * @brief perspective projection matrix
 * 
 * @param mv vertical field in radians
 * @param ma width/height ratio
 * @param mn close plane
 * @param mf distant plane
 */
CGMINLINE mat4 gmMat4perspective(float mv, float ma, float mn, float mf)
{
    float mt = tanf(mv * 0.5f);
    mat4 m = CGM_MAT4_INIT;
    m.m[0] = 1.0f / (ma * mt);
    m.m[5] = 1.0f / mt;
    m.m[10] = -(mf + mn) / (mf -mn);
    m.m[11] = -1.0f;
    m.m[14] = -(2.0f * mf * mn) / (mf - mn);
    return m;
}

/**
 * @brief lookat matrix
 * @param mey camera position
 * @param mc point to look at
 * @param mup up vector
 */
CGMINLINE mat4 gmMat4lookAt(vec3 mey, vec3 mc, vec3 mup)
{
    vec3 f = gmVec3normalize(gmVec3sub(mc, mey));
    vec3 s = gmVec3normalize(gmVec3cross(f, mup));
    vec3 u = gmVec3cross(s, f);
    mat4 m = gmMat4identity();

    m.m[0] = s.x;
    m.m[4] = s.y;
    m.m[8] = s.z;

    m.m[1] = u.x;
    m.m[5] = u.y;
    m.m[9] = u.z;

    m.m[2] =  -f.x;
    m.m[6] =  -f.y;
    m.m[10] = -f.z;

    m.m[12] = -gmVec3dot(s, mey);
    m.m[13] = -gmVec3dot(u, mey);
    m.m[14] =  gmVec3dot(f, mey);
    return m;
}

#endif