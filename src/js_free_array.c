#include "j_string.h"
#include "j_string_internal.h"

void js_free_array(j_string** array) {
  if (!array) {
    return;
  }
  for (size_t i = 0; array[i]; ++i) {
    js_free(array[i]);
  }
  free((void*)array);
}
