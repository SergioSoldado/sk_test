#include <assert.h>
#include <curl/curl.h>
#include <stdlib.h>

#include <sk/analytics/http.h>
#include <sk/macros.h>

struct _sk_ahttp {
  sk_handle* sk;
};

sk_ahttp* sk_ahttp_init() {
  sk_ahttp* ahttp = malloc(sizeof(sk_ahttp));
  ahttp->sk = sk_new();
  return ahttp;
}

void sk_ahttp_free(sk_ahttp* ahttp) {
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

sk_ahttp_result sk_ahttp_get(sk_ahttp* ahttp, char* url) {
  assert(ahttp != NULL);
  assert(url != NULL);
  assert(ahttp->sk != NULL);

  sk_handle* sk = ahttp->sk;
  sk_reset(sk);
  sk_set_url(sk, url);
  sk_set_write_callback(sk, null_writer);
  sk_set_http_verb(sk, SK_HTTP_GET);
  sk_perform(sk);

  sk_ahttp_result res = {0};
  return res;
}
