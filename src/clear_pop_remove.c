#include "j_string.h"
#include "j_string_internal.h"

js_result js_clear(j_string* str) {
  if (str->len == 0) {
    return NOOP;
  }
  memset(str->data, 0, str->capacity + 1);
  str->len = 0;
  return SUCCESS;
}

js_result js_pop_back(j_string* str) {
  if (str->len == 0) {
    return NOOP;
  }
  str->data[str->len - 1] = '\0';
  str->len--;
  return SUCCESS;
}

js_result js_pop_front(j_string* str) {
  if (str->len == 0) {
    return NOOP;
  }
  memmove(str->data, str->data + 1, str->len - 1);
  str->len--;
  str->data[str->len] = '\0';
  return SUCCESS;
}

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

js_result js_remove_back(j_string* str, size_t n) {
  if (str->len == 0 || n == 0) {
    return NOOP;
  }
  size_t to_remove = MIN(n, str->len);
  return js_remove(str, str->len - to_remove, to_remove);
}

js_result js_remove_front(j_string* str, size_t n) {
  if (str->len == 0 || n == 0) {
    return NOOP;
  }
  return js_remove(str, 0, n);
}
