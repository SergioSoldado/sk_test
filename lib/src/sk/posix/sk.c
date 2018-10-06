//
// Created by serj on 06/10/18.
//

#include <curl/curl.h>

#include <sk/sk.h>
#include <stdlib.h>
#include <assert.h>
#include <sk/macros.h>

struct _sk_handle {
  CURL* curl;
};

static inline void assert_handle(sk_handle* sk) {
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

sk_handle* sk_new(void) {
  sk_handle* h = malloc(sizeof(sk_handle));
  assert(h != NULL);
  h->curl = curl_easy_init();
  return h;
}

void sk_reset(sk_handle* sk) {
  assert_handle(sk);
  curl_easy_reset(sk->curl);
}

void sk_set_url(sk_handle* sk, char* url) {
  assert_handle(sk);
  assert(url != NULL);
  curl_easy_setopt(sk->curl, CURLOPT_URL, url);
}

void sk_free(sk_handle *handle) {
  assert(handle != NULL);
  curl_easy_cleanup(handle->curl);
  free(handle);
}

void sk_set_write_callback(sk_handle* sk, sk_writer_cb writer) {
  assert_handle(sk);
  assert(writer != NULL);
  curl_easy_setopt(sk->curl, CURLOPT_WRITEFUNCTION, writer);
}

void sk_set_http_verb(sk_handle* sk, SK_HTTP_VERB verb) {
  assert_handle(sk);
  switch(verb) {
    case SK_HTTP_GET:
      curl_easy_setopt(sk->curl, CURLOPT_HTTPGET, 1L);
      return;
    default:
      SK_ERROR("Invalid HTTP verb");
      return;
  }
}

void sk_perform(sk_handle* sk) {
  assert_handle(sk);
  curl_easy_perform(sk->curl);
}
