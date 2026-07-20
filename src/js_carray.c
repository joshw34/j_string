#include "j_string.h"
#include "j_string_internal.h"

static void free_str_array(char** array) {
  if (!array) {
    return;
  }
  for (size_t i = 0; array[i]; ++i) {
    free(array[i]);
  }
  free((void*)array);
}

char** js_carray(const j_string** array) {
  if (!array) {
    return NULL;
  }
  size_t size = js_array_size((j_string**)array);
  char** result = (char**)malloc((size + 1) * sizeof(char*));
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; array[i]; ++i) {
    result[i] = malloc(array[i]->len + 1);
    if (!result[i]) {
      free_str_array(result);
      return NULL;
    }
    memcpy(result[i], array[i]->data, array[i]->len);
    result[i][array[i]->len] = '\0';
  }
  return result;
}
