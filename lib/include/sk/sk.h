#include <stddef.h>
#ifndef __SK
#define __SK

typedef struct _sk_handle sk_handle;

/**
 * @brief Initialize the sk library. This function must only be run once during
 * @note This method is not thread safe, call it before starting new threads
 */
void sk_global_init(void);

/**
 * @brief Free resources allocated by sk_init()
 */
void sk_global_free(void);

/**
 * @brief Creates a new instance of sk_handle
 * @return A newly created sk_handle
 */
sk_handle* sk_new(void);

/**
 * @brief Free handle created by sk_handle_new()
 */
void sk_free(sk_handle *sk);

/**
 * @brief Unsets all previously set configuration on handle
 * @param sk handle to reset
 */
void sk_reset(sk_handle* sk);

/**
 * @brief Sets the target URL
 * @param sk sk_handle to configure
 */
void sk_set_url(sk_handle* sk, char* url);

/**
 * @brief Write data callback type
 */
typedef size_t (*sk_writer_cb)(void *, size_t, size_t , void *);

/**
 * @brief Set the function that will be called to store the output
 * @param sk sk_handle to configure
 * @param writer function called to store the request output
 */
void sk_set_write_callback(sk_handle* sk, sk_writer_cb writer);

typedef enum {
  SK_HTTP_GET
} SK_HTTP_VERB;

/**
 * @brief Configure the type of HTTP request
 * @param sk sk_handle to configure
 * @param verb HTTP verb
 */
void sk_set_http_verb(sk_handle* sk, SK_HTTP_VERB verb);

/**
 * @brief Perform a synchronous operation
 * @param sk previously configured sk_handle
 */
void sk_perform(sk_handle* sk);

#endif
