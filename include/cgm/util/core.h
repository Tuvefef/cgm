#ifndef CORE_H
#define CORE_H
/* core.h */

#define CGMINLINE static inline

#ifdef EXCP_FUNC

/**
 * @brief addition of two vectors using sse instructions
 * @note this macro is used for testing purposes only.
 * @param g0 vector 1 (float 4)
 * @param g1 vector 2 (float 4)
 * @param r0 vector where the result is saved
 */
#define GM_ADD_VEC4_SSE(g0, g1, r0) \
    __asm__ volatile( \
        "movups %1, %%xmm0\n" \
        "movups %2, %%xmm1\n" \
        "addps %%xmm1, %%xmm0\n" \
        "movups %%xmm0, %0\n" \
        : "=m"(r0) \
        :"m"(g0), "m"(g1) \
        :"xmm0", "xmm1" \
    )
#endif

#endif