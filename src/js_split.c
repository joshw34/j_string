#include "j_string.h"
#include "j_string_internal.h"

static bool add_string(char const* s, j_string** result, size_t str_n,
                       size_t char_count) {
  j_string* temp = js_new("");
  if (!temp) {
    return false;
  }
  js_result res = js_ncpy(temp, s, char_count);
  if (res != SUCCESS && res != NOOP) {
    js_free(temp);
    return false;
  }
  result[str_n] = temp;
  return true;
}

static bool split_string(char const* s, char c, j_string** result) {
  size_t str_count = 0;
  size_t i = 0;
  while (s[i]) {
    if (s[i] == c) {
      i++;
      continue;
    }
    size_t char_count = 0;
    while (s[i + char_count] && s[i + char_count] != c) {
      char_count++;
    }
    if (!add_string(s + i, result, str_count, char_count)) {
      return false;
    }
    str_count++;
    i += char_count;
  }
  return true;
}

static size_t count_words(char const* s, char c) {
  size_t word_count = 0;
  for (size_t i = 0; s[i]; ++i) {
    if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')) {
      word_count++;
    }
  }
  return word_count;
}

j_string** js_split(char const* s, char c) {
  if (!s) {
    return NULL;
  }
  size_t words = count_words(s, c);
  j_string** result = (j_string**)calloc(words + 1, sizeof(j_string*));
  if (!result) {
    return NULL;
  }
  if (!split_string(s, c, result)) {
    js_free_array(result);
    return NULL;
  }
  return result;
}
