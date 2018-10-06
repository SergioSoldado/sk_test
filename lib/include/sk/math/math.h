#ifndef __SK_MATH
#define __SK_MATH

/**
 * @file       sk/math/math.h
 * @brief      Declarations for sk math.
 */

#include <stddef.h>

//! Pointer to function which returns a pointer to double
typedef double* (*double_getter)(int index);

/**
 * @brief Calculate the median for a number of double values. This method performs the operation in place so
 * @param values pointer to values to calculate median for
 * @param num_values number of values
 * @return median
 * @note time log(n^2) implementation.
 */
double sk_calc_median(double* values, int num_values);

#endif
