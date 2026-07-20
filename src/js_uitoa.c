#include "j_string.h"
#include "j_string_internal.h"

#define max_len 12

j_string* js_uitoa(unsigned int n) {
  char buf[max_len];
  snprintf(buf, sizeof(buf), "%u", n);
  return js_new(buf);
}
