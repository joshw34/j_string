#include "j_string.h"
#include "j_string_internal.h"

static bool array_should_swap(const j_string* s1, const j_string* s2, sort_type type) {
  size_t min_len = (s1->len < s2->len) ? s1->len : s2->len;
  int cmp = strncmp(s1->data, s2->data, min_len);
  switch (type) {
    case ASCII:
      return cmp != 0 ? cmp > 0 : s1->len > s2->len;
    case LEN:
      return s1->len != s2->len ? s1->len > s2->len : cmp > 0;
    case REV_ASCII:
      return cmp != 0 ? cmp < 0 : s1->len < s2->len;
    case REV_LEN:
      return s1->len != s2->len ? s1->len < s2->len : cmp < 0;
  }
  return false;
}

js_result js_array_sort(j_string** array, sort_type type) {
  if (type != ASCII && type != LEN && type != REV_ASCII && type != REV_LEN) {
    return NOOP;
  }
  size_t size = js_array_size(array);
  if (size < 2) {
    return NOOP;
  }
  for (size_t i = 0; i < size - 1; ++i) {
    for (size_t j = 0; j < size - 1 - i; j++) {
      if (array_should_swap(array[j], array[j + 1], type)) {
        j_string* temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
  return SUCCESS;
}
