#include "j_string.h"
#include "j_string_internal.h"

js_result js_remove(j_string* str, size_t start, size_t n) {
  if (str->len == 0 || n == 0) {
    return NOOP;
  }
  if (start >= str->len) {
    return ERR_RANGE;
  }
  size_t to_remove = (start + n <= str->len) ? n : str->len - start;
  size_t tail_len = str->len - start - to_remove;
  if (tail_len > 0) {
    memmove(str->data + start, str->data + start + to_remove, tail_len);
  }
  str->len -= to_remove;
  memset(str->data + str->len, 0, to_remove);
  return SUCCESS;
}
