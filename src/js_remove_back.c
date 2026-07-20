#include "j_string.h"
#include "j_string_internal.h"

js_result js_remove_back(j_string* str, size_t n) {
  if (str->len == 0 || n == 0) {
    return NOOP;
  }
  size_t to_remove = MIN(n, str->len);
  return js_remove(str, str->len - to_remove, to_remove);
}
