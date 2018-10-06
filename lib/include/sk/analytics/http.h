#ifndef __SK_ANALYTICS_HTTP
#define __SK_ANALYTICS_HTTP
/**
 * @file       sk/analytics/http.h
 * @brief      Functions for http analytics.
 */

#include <stddef.h>
#include <stdbool.h>
#include <sk/sk.h>

typedef struct _sk_ahttp sk_ahttp;

/**
 * @brief Create instance of sk analytics http
 * @return handle to newly created instance
 */
sk_ahttp *sk_ahttp_init(void);

/**
 * @brief Frees instance of sk analytics http
 * @param handle pointer to instance previously created by http_init()
 */
void sk_ahttp_free(sk_ahttp *ahttp);

typedef struct sk_ahttp_result {
  int r0;
} sk_ahttp_result;

sk_ahttp_result sk_ahttp_get(sk_ahttp *ahttp, char *url);

#endif
