#ifndef __SK
#define __SK

/**
 * @file       sk/sk.h
 * @brief      Declarations for sk.
 */

#include <stddef.h>

//! sk handle data type
typedef struct _sk_handle sk_handle;

//! sk return codes
typedef enum {
  SK_OK,
  SK_ERROR,
} sk_ret;

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
sk_handle *sk_new(void);

/**
 * @brief Free handle created by sk_handle_new()
 */
void sk_free(sk_handle *sk);

/**
 * @brief Unsets all previously set configuration on handle
 * @param sk handle to reset
 */
void sk_reset(sk_handle *sk);

/**
 * @brief Sets the target URL
 * @param sk sk_handle to configure
 */
void sk_set_url(sk_handle *sk, char *url);

/**
 * @brief Write data callback type
 */
typedef size_t (*sk_writer_cb)(void *, size_t, size_t, void *);

/**
 * @brief Set the function that will be called to store the output
 * @param sk sk_handle to configure
 * @param writer function called to store the request output
 */
void sk_set_write_callback(sk_handle *sk, sk_writer_cb writer);

//! Types of HTTP verbs
typedef enum {
  SK_HTTP_GET  //! HTTP get
} SK_HTTP_VERB;

/**
 * @brief Configure the type of HTTP request
 * @param sk sk_handle to configure
 * @param verb HTTP verb
 */
void sk_set_http_verb(sk_handle *sk, SK_HTTP_VERB verb);

/**
 * @brief Perform a synchronous operation
 * @param sk previously configured sk_handle
 * @return SK_OK if successful, SK_ERROR otherwise
 */
sk_ret sk_perform(sk_handle *sk);

/**
 * @brief Contains several transfer time values
 *   |
 *   |--NAMELOOKUP
 *   |--|--CONNECT
 *   |--|--|--APPCONNECT
 *   |--|--|--|--PRETRANSFER
 *   |--|--|--|--|--STARTTRANSFER
 *   |--|--|--|--|--|--TOTAL
 *   |--|--|--|--|--|--REDIRECT
 */
typedef struct sk_time_info {
  double namelookup_time_secs;  //! name lookup time in seconds
  double connect_time_secs;  //! connect time in seconds
  double start_transfer_time;  //! start transfer time in seconds
  double total_time_secs;  //! total time in seconds
} sk_time_info;

/**
 * @brief Get last operation response code
 * @param sk sk_handle used to perform an action
 * @param code pointer to address where code value is written to
 * @return SK_OK if successful, SK_ERROR otherwise
 */
sk_ret sk_get_response_code(sk_handle *sk, long *code);

/**
 * @brief Get last operation information
 * @param sk sk_handle used to perform an operation
 * @param code pointer to previously allocated structure where result is written to
 * @return SK_OK if successful, SK_ERROR otherwise
 */
sk_ret sk_get_time_info(sk_handle *sk, sk_time_info *time_info);

#endif
