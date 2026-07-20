#include "j_string.h"
#include "j_string_internal.h"

static bool check_char(const char c, const char* set) {
  for (size_t i = 0; set[i]; ++i) {
    if (c == set[i]) {
      return true;
    }
  }
  return false;
}

static size_t count_backwards(char const* s1, size_t len, char const* set) {
  for (size_t i = len; i > 0; --i) {
    if (!check_char(s1[i - 1], set)) {
      return i;
    }
  }
  return 0;
}

static size_t count_forward(char const* s1, size_t len, char const* set) {
  for (size_t i = 0; s1[i]; ++i) {
    if (!check_char(s1[i], set)) {
      return i;
    }
  }
  return len;
}

j_string* js_trim(char const* s1, char const* set) {
  if (!s1 || !set) {
    return NULL;
  }
  size_t s1_len = strlen(s1);
  size_t start = count_forward(s1, s1_len, set);
  size_t stop = count_backwards(s1, s1_len, set);
  size_t new_size = (start >= s1_len || stop <= start) ? 0 : stop - start;
  j_string* result = js_new("");
  if (!result) {
    return NULL;
  }
  if (new_size == 0) {
    return result;
  }
  if (js_ncpy(result, s1 + start, new_size) != SUCCESS) {
    js_free(result);
    return NULL;
  }
  return result;
}
