#ifndef CGM_MAT4_H
#define CGM_MAT4_H

/**
 * @file mat4.h
 * 
 */

#include "core.h"
#include "structs/stcmat4.h"

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
 * @brief mat4 inverse
 * 
 * calculates the inverse of mat4 in column-major format
 * 
 * @note generic function (extensive)
 */
CGMINLINE mat4 gmMat4inverse(mat4 m)
{
    mat4 r;

    float *ma = m.m;
    float *mo = r.m;

    mo[0] = ma[5] * ma[10]* ma[15] - 
            ma[5] * ma[11]* ma[14] - 
            ma[9] * ma[6] * ma[15] + 
            ma[9] * ma[7] * ma[14] + 
            ma[13]* ma[6] * ma[11] - 
            ma[13]* ma[7] * ma[10];

    mo[4] = -ma[4] * ma[10]* ma[15] + 
             ma[4] * ma[11]* ma[14] + 
             ma[8] * ma[6] * ma[15] - 
             ma[8] * ma[7] * ma[14] - 
             ma[12]* ma[6] *ma[11]  + 
             ma[12]* ma[7] *ma[10];

    mo[8] = ma[4] * ma[9] * ma[15] - 
            ma[4] * ma[11]* ma[13] - 
            ma[8] * ma[5] * ma[15]+ 
            ma[8] * ma[7] * ma[13] + 
            ma[12]* ma[5] * ma[11] - 
            ma[12]* ma[7] * ma[9];

    mo[12] = -ma[4] * ma[9] * ma[14] + 
              ma[4] * ma[10]* ma[13] + 
              ma[8] * ma[5] * ma[14] - 
              ma[8] * ma[6] * ma[13] - 
              ma[12]* ma[5] * ma[10] + 
              ma[12]* ma[6] * ma[9];

    mo[1] = -ma[1] * ma[10]* ma[15] + 
             ma[1] * ma[11]* ma[14] + 
             ma[9] * ma[2] * ma[15] - 
             ma[9] * ma[3] * ma[14] - 
             ma[13]* ma[2] * ma[11] + 
             ma[13]* ma[3] * ma[10];

    mo[5] = ma[0] * ma[10]* ma[15] - 
            ma[0] * ma[11]* ma[14] - 
            ma[8] * ma[2] * ma[15] + 
            ma[8] * ma[3] * ma[14] + 
            ma[12]* ma[2] * ma[11] - 
            ma[12]* ma[3] * ma[10];

    mo[9] = -ma[0] * ma[9] * ma[15] + 
             ma[0] * ma[11]* ma[13] + 
             ma[8] * ma[1] * ma[15] - 
             ma[8] * ma[3] * ma[13] - 
             ma[12]* ma[1] * ma[11] + 
             ma[12]* ma[3] * ma[9];

    mo[13] = ma[0] * ma[9] * ma[14] - 
             ma[0] * ma[10]* ma[13] - 
             ma[8] * ma[1] * ma[14] + 
             ma[8] * ma[2] * ma[13] + 
             ma[12]* ma[1] * ma[10] - 
             ma[12]* ma[2] * ma[9];

    mo[2] =  ma[1] * ma[6] * ma[15] - 
             ma[1] * ma[7] * ma[14] - 
             ma[5] * ma[2] * ma[15] + 
             ma[5] * ma[3] * ma[14] + 
             ma[13]* ma[2] * ma[7] - 
             ma[13]* ma[3] * ma[6];

    mo[6] = -ma[0] * ma[6] * ma[15] + 
             ma[0] * ma[7] * ma[14] + 
             ma[4] * ma[2] * ma[15] - 
             ma[4] * ma[3] * ma[14] - 
             ma[12]* ma[2] * ma[7] + 
             ma[12]* ma[3] * ma[6];

    mo[10] = ma[0] * ma[5] * ma[15] - 
             ma[0] * ma[7] * ma[13] - 
             ma[4] * ma[1] * ma[15] + 
             ma[4] * ma[3] * ma[13] + 
             ma[12]* ma[1] * ma[7] - 
             ma[12]* ma[3] * ma[5];

    mo[14] = -ma[0] * ma[5] * ma[14] + 
              ma[0] * ma[6] * ma[13] + 
              ma[4] * ma[1] * ma[14] - 
              ma[4] * ma[2] * ma[13] - 
              ma[12]* ma[1] * ma[6] + 
              ma[12]* ma[2] * ma[5];

    mo[3] = -ma[1] * ma[6] * ma[11] + 
             ma[1] * ma[7] * ma[10] + 
             ma[5] * ma[2] * ma[11] - 
             ma[5] * ma[3] * ma[10] - 
             ma[9] * ma[2] * ma[7] + 
             ma[9] * ma[3] * ma[6];

    mo[7] = ma[0] * ma[6] * ma[11] - 
            ma[0] * ma[7] * ma[10] - 
            ma[4] * ma[2] * ma[11] + 
            ma[4] * ma[3] * ma[10] + 
            ma[8] * ma[2] * ma[7] - 
            ma[8] * ma[3] * ma[6];

    mo[11] = -ma[0] * ma[5] * ma[11] + 
              ma[0] * ma[7] * ma[9] + 
              ma[4] * ma[1] * ma[11] - 
              ma[4] * ma[3] * ma[9] - 
              ma[8] * ma[1] * ma[7] + 
              ma[8] * ma[3] * ma[5];

    mo[15] = ma[0] * ma[5] * ma[10] - 
             ma[0] * ma[6] * ma[9] - 
             ma[4] * ma[1] * ma[10] + 
             ma[4] * ma[2] * ma[9] + 
             ma[8] * ma[1] * ma[6] -
             ma[8] * ma[2] * ma[5];

    float dt = ma[0] * mo[0] + ma[1] * mo[4] + ma[2] * mo[8] + ma[3] * mo[12];

    float Inverse = 1.0f / dt;

    for(int i = 0; i < 16; i++)
    {
        mo[i] *= Inverse;
    }

    return r;
}

/**
 * @brief mat4 x vec4
 * multiply a mat4 by a vec4
 * 
 * @return vec4
 */
CGMINLINE vec4 gmMat4mulVec4(mat4 m, vec4 v)
{
    vec4 r;
    r.x = m.m[0]  * v.x + m.m[4]  * v.y + m.m[8]  * v.z + m.m[12] * v.w;
    r.y = m.m[1]  * v.x + m.m[5]  * v.y + m.m[9]  * v.z + m.m[13] * v.w;
    r.z = m.m[2]  * v.x + m.m[6]  * v.y + m.m[10] * v.z + m.m[14] * v.w;
    r.w = m.m[3]  * v.x + m.m[7]  * v.y + m.m[11] * v.z + m.m[15] * v.w;
    return r;
}

#endif