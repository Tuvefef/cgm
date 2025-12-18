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

/**
 * @brief create an identity matrix
 */
CGMINLINE mat4 gmMat4identity(void)
{
    mat4 r = {0};
    r.m[0]  = 1.0f;
    r.m[5]  = 1.0f;
    r.m[10] = 1.0f;
    r.m[15] = 1.0f;
    return r;
}

#endif