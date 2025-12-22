#ifndef UTIL_GRAPHICS_MATH
#define UTIL_GRAPHICS_MATH

/**
 * @file ugm.h
 */

#include "util/core.h"
#include <math.h>

#define CGM_EPSILON 1e-8f
#ifndef CGM_AUTO_NORMALIZE
/*
 * @brief `GCM_ASSUME_NORMALIZED`
 *assume that certain vectors are normalized.
 *will not internally normalize normal vectors
 *
 *default: 0
 */
#define CGM_AUTO_NORMALIZE 0
#endif

#define GMMIN(x, y) (((x) < (y)) ? (x) : (y))
#define GMMAX(x, y) (((x) > (y)) ? (x) : (y))

/*
 * @brief limits a vector between a minimum and a maximum
 *
 */
CGMINLINE float gmClamp(float x, float min, float max)
{
    return GMMAX(min, GMMIN(x, max));
}

/*
 * @brief fractional part of the vector
 * 
 * equivalent to `x - floor(x)`
 */
CGMINLINE float gmFract(float x)
{
    return x - floorf(x);
}

/*
 * @brief linear interpolation between two vals
 * 
 * @param a init vector
 * @param b final vector
 * @param t interpolation factor [0, 1]
 */
CGMINLINE float gmMix(float a, float b, float t)
{
    return a + (b - a) * t;
}

/*
 * @brief Returns 0.0 if x < edge, otherwise returns 1.0
 *
 * @param e threshold value
 * @param x input value
 *
 * @return 0.0 if x < edge, 1.0 otherwise
 */
CGMINLINE float gmStep(float e, float x)
{
    return (x < e) ? 0.0f : 1.0f;
}

/*
 * @brief cubic smoothing
 *The first derivative is zero at t = 0 and t = 1.
 *
 * @param t interpolation parameter, typically in range [0, 1]
 *
 * @return smoothed value
 */
CGMINLINE float gmSmooth(float t)
{
    return t * t * (3.0f - 2.0f * t);
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
CGMINLINE float gmSmoothstep(float e0, float e1, float x)
{
    float t = gmClamp((x - e0) / (e1 - e0), 0.0f, 1.0f);
    return gmSmooth(t);
}

CGMINLINE float gmFade(float t)
{
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

#endif