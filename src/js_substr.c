#include "j_string.h"
#include "j_string_internal.h"

j_string* js_substr(const char* s, size_t start, size_t len) {
  if (!s) {
    return NULL;
  }
  j_string* result = js_new("");
  if (!result) {
    return NULL;
  }
  size_t s_len = strlen(s);
  if (start > s_len || s_len == 0) {
    return result;
  }
  size_t new_len = ((s_len - start) > len) ? len : s_len - start;
  js_result res = js_ncpy(result, s + start, new_len);
  if (res != SUCCESS && res != NOOP) {
    js_free(result);
    return NULL;
  }
  return result;
}
