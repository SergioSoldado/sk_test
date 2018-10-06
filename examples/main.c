#include <sk/sk.h>
#include <sk/analytics/http.h>
#include <stdio.h>

int main() {
  sk_global_init();

  sk_ahttp *ahttp = sk_ahttp_init();

  sk_ret ret = sk_ahttp_get(ahttp, "http://www.google.com");
  if (ret == SK_OK) {
    printf("%ld %f %f %f %f\n", ahttp->response_code,
           ahttp->time_info.namelookup_time_secs,
           ahttp->time_info.connect_time_secs,
           ahttp->time_info.start_transfer_time,
           ahttp->time_info.total_time_secs);
  }

  sk_ahttp_free(ahttp);

  sk_global_free();
  return 0;
}
