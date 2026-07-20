#include "j_string.h"
#include "j_string_internal.h"

js_result js_remove_front(j_string* str, size_t n) {
  if (str->len == 0 || n == 0) {
    return NOOP;
  }
  return js_remove(str, 0, n);
}
