/// @file
///
/// Custom asserts.
///
#pragma once

#include <stdlib.h> // for abort()

/// Checks \p COND and prints message to stderr on error.
#define SOFT_ASSERT(COND)                                              \
    do {                                                               \
        if (COND)                                                      \
            break;                                                     \
        fprintf(stderr, "%s:%d: assertion \"%s\" failed.\n", __FILE__, \
                __LINE__, #COND);                                      \
    } while (0)

/// Checks \p COND, prints message to stderr and aborts on error.
#define HARD_ASSERT(COND)  \
    do {                   \
        SOFT_ASSERT(COND); \
        abort();           \
    } while (0)

/// Checks \p COND, prints message to stderr and executes \p CODE
#define FUNC_ASSERT(COND, CODE) \
    SOFT_ASSERT(COND);          \
    CODE
