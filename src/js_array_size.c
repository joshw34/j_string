#include "j_string.h"
#include "j_string_internal.h"

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
