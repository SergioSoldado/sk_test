#include <sk/sk.h>
#include <sk/analytics/http.h>

int main() {
  sk_global_init();

  sk_ahttp* ahttp = sk_ahttp_init();

  sk_ahttp_get(ahttp, "http://www.google.com");

  sk_ahttp_free(ahttp);

  sk_global_free();
  return 0;
}
