#ifndef CORE_H
#define CORE_H
/* core.h */

#define CGMINLINE static inline

#ifndef CGM_ASSUME_NORMALIZED
/*
 * @brief `GCM_ASSUME_NORMALIZED`
 *assume that certain vectors are normalized.
 *will not internally normalize normal vectors
 *
 *default: 0
 */
#define CGM_ASSUME_NORMALIZED 0
#endif

#define GMMIN(x, y) (((x) < (y)) ? (x) : (y))
#define GMMAX(x, y) (((x) > (y)) ? (x) : (y))

#endif