/**
 * @file       src/sk/posix/sk.c
 * @brief      Definitions for sk posix implementation.
 */

#include <assert.h>
#include <stdlib.h>

#include <curl/curl.h>

#include <sk/macros.h>
#include <sk/sk.h>

struct _sk_handle {
  CURL *curl;
};

static inline sk_ret curl_to_sk_code(CURLcode code) {
  return code == CURLE_OK ? SK_OK : SK_ERROR;
}

static inline void assert_handle(sk_handle *sk) {
  assert(sk);
  assert(sk->curl);
}

void sk_global_init(void) {
  // load curl with every available module
  curl_global_init(CURL_GLOBAL_ALL);
}

void sk_global_free(void) {
  curl_global_cleanup();
}

sk_handle *sk_new(void) {
  sk_handle *h = malloc(sizeof(sk_handle));
  assert(h != NULL);
  h->curl = curl_easy_init();
  return h;
}

void sk_reset(sk_handle *sk) {
  assert_handle(sk);
  curl_easy_reset(sk->curl);
}

void sk_set_url(sk_handle *sk, char *url) {
  assert_handle(sk);
  assert(url != NULL);
  curl_easy_setopt(sk->curl, CURLOPT_URL, url);
}

void sk_free(sk_handle *handle) {
  assert(handle != NULL);
  curl_easy_cleanup(handle->curl);
  free(handle);
}

void sk_set_write_callback(sk_handle *sk, sk_writer_cb writer) {
  assert_handle(sk);
  assert(writer != NULL);
  curl_easy_setopt(sk->curl, CURLOPT_WRITEFUNCTION, writer);
}

void sk_set_http_verb(sk_handle *sk, SK_HTTP_VERB verb) {
  assert_handle(sk);
  switch (verb) {
    case SK_HTTP_GET:curl_easy_setopt(sk->curl, CURLOPT_HTTPGET, 1L);
      return;
    default:SK_ERROR("Invalid HTTP verb");
      return;
  }
}

sk_ret sk_perform(sk_handle *sk) {
  assert_handle(sk);
  return curl_to_sk_code(curl_easy_perform(sk->curl));
}

sk_ret sk_get_response_code(sk_handle *sk, long *code) {
  assert_handle(sk);
  assert(code != NULL);
  return curl_to_sk_code(curl_easy_getinfo(sk->curl, CURLINFO_RESPONSE_CODE, code));
}

sk_ret sk_get_time_info(sk_handle *sk, sk_time_info *time_info) {
  assert_handle(sk);
  assert(time_info != NULL);

  const int items[] = {CURLINFO_NAMELOOKUP_TIME,
                       CURLINFO_CONNECT_TIME,
                       CURLINFO_STARTTRANSFER_TIME,
                       CURLINFO_TOTAL_TIME,
  };
  const int num_items = (int) (sizeof(items) / sizeof(items[0]));

  double *dptr = &time_info->namelookup_time_secs;

  for (int i = 0; i < num_items; ++i) {
    CURLcode res = curl_easy_getinfo(sk->curl, items[i], &dptr[i]);
    if (res != CURLE_OK) {
      return curl_to_sk_code(res);
    }
  }

  return SK_OK;
}
