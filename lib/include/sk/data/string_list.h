#ifndef __SK_DATA_STRING_LIST
#define __SK_DATA_STRING_LIST

/**
 * @file       sk/data/string_list.h
 * @brief      Declarations for sk string list.
 */

//! sk string datatypes
typedef struct curl_slist *sk_string_list;

/**
 * @brief Create a new string list
 * @return string list instance
 */
sk_string_list sk_string_list_new(void);

/**
 * @brief Append string to string list
 * @param list string list to append to
 * @param str string to append
 * @return resulting string list
 */
sk_string_list sk_string_list_append(sk_string_list *list, char *str);

/**
 * @brief Free string list
 * @param list string list to free
 */
void sk_string_list_free(sk_string_list list);

#endif
