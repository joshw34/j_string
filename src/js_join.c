#include "j_string.h"
#include "j_string_internal.h"

j_string* js_join(const char* s1, const char* s2) {
  if (!s1 || !s2) {
    return NULL;
  }
  j_string* result = js_new(s1);
  if (!result) {
    return NULL;
  }
  js_result res = js_app_back(result, s2);
  if (res != SUCCESS && res != NOOP) {
    js_free(result);
    return NULL;
  }
  return result;
}
