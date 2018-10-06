/**
 * @file       src/sk/data/string_list.c
 * @brief      Definitions for sk string list.
 */

#include <assert.h>

#include <curl/curl.h>

#include <sk/data/string_list.h>

sk_string_list sk_string_list_new(void) {
  return NULL;
}

sk_string_list sk_string_list_append(sk_string_list *list, char *str) {
  assert(str != NULL);
  *list = curl_slist_append(*list, str);
  return *list;
}

void sk_string_list_free(sk_string_list list) {
  assert(list != NULL);
  curl_slist_free_all(list);
}
