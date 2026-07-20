#include "j_string.h"
#include "j_string_internal.h"

j_string* js_itoa(int n) {
  char buf[12];
  snprintf(buf, sizeof(buf), "%d", n);
  return js_new(buf);
}

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

js_result js_tolower(j_string* str) {
  for (size_t i = 0; i < str->len; ++i) {
    str->data[i] = (char)tolower(str->data[i]);
  }
  return SUCCESS;
}

js_result js_toupper(j_string* str) {
  for (size_t i = 0; i < str->len; ++i) {
    str->data[i] = (char)toupper(str->data[i]);
  }
  return SUCCESS;
}

j_string* js_uitoa(unsigned int n) {
  char buf[12];
  snprintf(buf, sizeof(buf), "%u", n);
  return js_new(buf);
}
