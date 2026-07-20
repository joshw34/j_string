#include "j_string.h"
#include "j_string_internal.h"

js_result js_ncpy(j_string* dest, const char* src, size_t n) {
  if (!src || src[0] == '\0') {
    return NOOP;
  }
  size_t src_len = strlen(src);
  size_t cpy_len = (n < src_len) ? n : src_len;
  bool free_temp = false;
  char* temp = get_safe_new_data(dest->data, dest->len, src, cpy_len, &free_temp);
  if (!temp) {
    return ERR_ALLOC;
  }
  if (!ensure_capacity_replace(dest, cpy_len)) {
    free_if_true(free_temp, temp);
    return ERR_ALLOC;
  }
  memcpy(dest->data, temp, cpy_len);
  dest->data[cpy_len] = '\0';
  dest->len = cpy_len;
  free_if_true(free_temp, temp);
  return SUCCESS;
}
