#include "j_string.h"
#include "j_string_internal.h"

js_result js_reverse(j_string* str) {
  size_t len = str->len;
  if (len < 2) {
    return NOOP;
  }
  char* data = str->data;
  for (size_t i = 0, j = len - 1; i < j; ++i, --j) {
    char temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }
  return SUCCESS;
}
