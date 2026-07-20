#include "j_string.h"
#include "j_string_internal.h"

static size_t str_array_size(const char** array) {
  size_t i = 0;
  if (!array) {
    return 0;
  }
  while (array[i]) {
    i++;
  }
  return i;
}

j_string** js_array(const char** src) {
  if (!src) {
    return NULL;
  }
  size_t src_size = str_array_size(src);
  j_string** result = (j_string**)malloc((src_size + 1) * sizeof(j_string*));
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; src[i]; ++i) {
    result[i] = js_new(src[i]);
    if (!result[i]) {
      js_free_array(result);
      return NULL;
    }
  }
  return result;
}
