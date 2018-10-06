#ifndef _SK_MACROS
#define _SK_MACROS

/**
 * @file       sk/macros.h
 * @brief      Common declarations for sk.
 */

// NOTE this shouldn't be defined here in commercial code
#define _SK_DEBUG

#ifdef _SK_DEBUG
#include <assert.h>
#endif

#define SK_UNUSED(x) (void)(x)

#ifdef _SK_DEBUG
#define SK_ERROR(msg) \
            do { fprintf(stderr,"%s %s %d %s", __FILE__, __FUNCTION__, __LINE__, msg); assert(0); } while (0)
#else
// ToDo this doesn't seem quite right, I am used to exceptions and am spending too much time on these things
#define SK_ERROR(msg)
#endif

#endif
