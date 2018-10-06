#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include <sk/sk.h>
#include <sk/analytics/http.h>
#include <sk/math/math.h>
#include <sk/data/string_list.h>

void usage(char *name) {
  printf("usage: %s -n <integer> -H \"Header-name: Header-value\" -H <another> ...\n", name);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    usage(*argv);
    return 0;
  }

  size_t num_samples = 0;
  sk_string_list http_headers = sk_string_list_new();

  int c = 0;
  while ((c = getopt(argc, argv, "H:n:")) != -1) {
    switch (c) {
      case 'n':
        if (num_samples > 0) {
          return 1;
        }
        num_samples = (size_t) atoi(optarg);
        break;
      case 'H':
        sk_string_list_append(&http_headers, optarg);
        break;
      default:usage(*argv);
        return 1;
    }
  }

  sk_global_init();

  // Maybe a better design wouldn't need these caches
  double *list_namelookup_time_secs = calloc(num_samples, sizeof(double));
  double *list_connect_time_secs = calloc(num_samples, sizeof(double));
  double *list_start_transfer_secs = calloc(num_samples, sizeof(double));
  double *list_total_time_secs = calloc(num_samples, sizeof(double));

  int n_reqs = 0;
  for (int i = 0; i < (int) num_samples; ++i) {
    sk_ahttp *ahttp = sk_ahttp_init();
    sk_ret ret = sk_ahttp_get(ahttp, "http://www.google.com", http_headers);
    if (ret != SK_OK) {
      // ToDo deal with this in a better way
      fprintf(stderr, "Error");
      continue;
    }

    list_namelookup_time_secs[n_reqs] = ahttp->time_info.namelookup_time_secs;
    list_connect_time_secs[n_reqs] = ahttp->time_info.connect_time_secs;
    list_start_transfer_secs[n_reqs] = ahttp->time_info.start_transfer_secs;
    list_total_time_secs[n_reqs] = ahttp->time_info.total_time_secs;
    ++n_reqs;

    printf("SKTEST;%s;%ld;%f;%f;%f;%f\n",
           ahttp->network_address,
           ahttp->response_code,
           sk_calc_median(list_namelookup_time_secs, n_reqs),
           sk_calc_median(list_connect_time_secs, n_reqs),
           sk_calc_median(list_start_transfer_secs, n_reqs),
           sk_calc_median(list_total_time_secs, n_reqs)
    );

    sk_ahttp_free(ahttp);
  }

  free(list_namelookup_time_secs);
  free(list_connect_time_secs);
  free(list_start_transfer_secs);
  free(list_total_time_secs);
  sk_string_list_free(http_headers);

  sk_global_free();
  return 0;
}
