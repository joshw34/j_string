#include "j_string.h"
#include "j_string_internal.h"

char js_at(const j_string* str, size_t index) {
  if (index >= str->len) {
    return '\0';
  }
  return str->data[index];
}

const char* js_cstr(const j_string* str) {
  return str->data;
}

size_t js_len(const j_string* str) {
  return str->len;
}

bool js_empty(const j_string* str) {
  return str->len == 0;
}

size_t js_array_size(j_string** array) {
  if (!array) {
    return 0;
  }
  size_t i = 0;
  while (array[i]) {
    ++i;
  }
  return i;
}
