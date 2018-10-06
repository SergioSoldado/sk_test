/**
 * @file       src/sk/math/math.c
 * @brief      Definitions for sk math.
 */

#include <assert.h>
#include <sk/math/math.h>

double sk_calc_median(double* values, int num_values) {
  assert(values);
  assert(num_values >= 0);
  double temp;

  // log(n^2)
  for (int i = 0; i < num_values - 1; i++) {
    for (int j = i + 1; j < num_values; j++) {
      if (values[j] < values[i]) {
        // swap elements
        temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }

  return (num_values % 2 == 0) ? ((values[num_values / 2] + values[num_values / 2 - 1]) / 2.0) : values[num_values / 2];
}
