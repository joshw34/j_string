#include "j_string.h"
#include "j_string_internal.h"

void js_free(j_string* str) {
  if (!str) {
    return;
  }
  if (str->data) {
    free(str->data);
  }
  free(str);
}
