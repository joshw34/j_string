#include "j_string.h"
#include "j_string_internal.h"

js_result js_tolower(j_string* str) {
  for (size_t i = 0; i < str->len; ++i) {
    str->data[i] = (char)tolower(str->data[i]);
  }
  return SUCCESS;
}
