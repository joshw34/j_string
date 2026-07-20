#include "j_string.h"
#include "j_string_internal.h"

static const size_t MIN_CAPACITY = 32;

void js_free(j_string* str) {
  if (!str) {
    return;
  }
  if (str->data) {
    free(str->data);
  }
  free(str);
}

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

j_string* js_dup(const j_string* src) {
  return src ? js_new(src->data) : NULL;
}

j_string* js_new(const char* data) {
  j_string* str = malloc(sizeof(j_string));
  if (!str) {
    return NULL;
  }
  str->len = data ? strlen(data) : 0;
  str->capacity = (str->len <= MIN_CAPACITY) ? MIN_CAPACITY : str->len;
  str->data = malloc(str->capacity + 1);
  if (!str->data) {
    js_free(str);
    return NULL;
  }
  if (data) {
    memcpy(str->data, data, str->len);
  }
  str->data[str->len] = '\0';
  return str;
}
