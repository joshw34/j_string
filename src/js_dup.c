#include "j_string.h"
#include "j_string_internal.h"

j_string* js_dup(const j_string* src) {
  return js_new(src->data);
}
