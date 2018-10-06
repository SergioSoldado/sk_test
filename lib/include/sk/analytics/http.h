#ifndef __SK_ANALYTICS_HTTP
#define __SK_ANALYTICS_HTTP

/**
 * @file       sk/analytics/http.h
 * @brief      Declarations for sk http analytics.
 */

#include <stddef.h>
#include <stdbool.h>

#include <sk/sk.h>
#include <sk/data/string_list.h>

//! sk ahhtp handle data type
typedef struct sk_ahttp {
  sk_handle *sk;
  sk_time_info time_info;
  char *network_address;
  long response_code;
} sk_ahttp;

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

/**
 * @brief Perform an http get
 * @param ahttp ahttp handle
 * @param url target uri
 * @return SK_OK if successful, SK_ERROR otherwise
 */
sk_ret sk_ahttp_get(sk_ahttp *ahttp, char *uri, sk_string_list headers);

#endif
