#include "j_string.h"
#include "j_string_internal.h"

j_string** js_empty_array(size_t size) {
  j_string** result = (j_string**)malloc((size + 1) * sizeof(j_string*));
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; i < size; ++i) {
    result[i] = js_new(NULL);
    if (!result[i]) {
      js_free_array(result);
      return NULL;
    }
  }
  return result;
}
