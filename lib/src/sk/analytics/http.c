/**
 * @file       src/sk/analytics/http.c
 * @brief      Definitions for sk http analytics.
 */

#include <assert.h>
#include <stdlib.h>

#include <curl/curl.h>

#include <sk/analytics/http.h>
#include <sk/macros.h>

sk_ahttp *sk_ahttp_init() {
  sk_ahttp *ahttp = malloc(sizeof(sk_ahttp));
  ahttp->sk = sk_new();
  return ahttp;
}

void sk_ahttp_free(sk_ahttp *ahttp) {
  assert(ahttp != NULL);
  sk_free(ahttp->sk);
  free(ahttp);
}

/**
 * @brief Custom curl writer to hide default output to stdout
 * @param buffer unused
 * @param size unused
 * @param nmemb unused
 * @param userp unused
 * @return
 */
static size_t null_writer(void *buffer, size_t size, size_t nmemb, void *userp) {
  SK_UNUSED(buffer);
  SK_UNUSED(size);
  SK_UNUSED(nmemb);
  SK_UNUSED(userp);
  return size * nmemb;
}

sk_ret sk_ahttp_get(sk_ahttp *ahttp, char *uri, sk_string_list headers) {
  assert(ahttp != NULL);
  assert(ahttp->sk != NULL);
  assert(uri != NULL);
  assert(ahttp->sk != NULL);

  sk_handle *sk = ahttp->sk;
  sk_reset(sk);
  sk_set_url(sk, uri);
  sk_set_write_callback(sk, null_writer);
  sk_set_http_verb(sk, SK_HTTP_GET);
  sk_set_http_headers(sk, headers);

  sk_ret ret = sk_perform(sk);
  if (ret != SK_OK) return ret;

  ret = sk_get_address(sk, &ahttp->network_address);
  if (ret != SK_OK) return ret;

  ret = sk_get_response_code(sk, &ahttp->response_code);
  if (ret != SK_OK) return ret;

  ret = sk_get_time_info(sk, &ahttp->time_info);
  if (ret != SK_OK) return ret;

  return SK_OK;
}
