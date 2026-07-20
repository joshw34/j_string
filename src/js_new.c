#include "j_string.h"
#include "j_string_internal.h"

// ACCESS
char js_at(const j_string* str, size_t index) {
  if (index >= str->len) {
    return '\0';
  }
  return str->data[index];
}

const char* js_cstr(const j_string* str) {
  return str->data;
}

size_t js_len(const j_string* str) {
  return str->len;
}

bool js_empty(const j_string* str) {
  return str->len == 0;
}

// STRING MUTATIONS
js_result js_app_back(j_string* str, const char* new_data) {
  if (!new_data || new_data[0] == '\0') {
    return NOOP;
  }
  size_t new_data_len = strlen(new_data);
  bool free_temp = false;
  char* temp = get_safe_new_data(str->data, str->len, new_data, new_data_len, &free_temp);
  if (!temp) {
    return ERR_ALLOC;
  }
  if (!ensure_capacity_insert(str, new_data_len)) {
    free_if_true(free_temp, temp);
    return ERR_ALLOC;
  }
  memcpy(str->data + str->len, temp, new_data_len);
  str->len += new_data_len;
  str->data[str->len] = '\0';
  free_if_true(free_temp, temp);
  return SUCCESS;
}

js_result js_app_front(j_string* str, const char* new_data) {
  if (!new_data || new_data[0] == '\0') {
    return NOOP;
  }
  size_t new_data_len = strlen(new_data);
  bool free_temp = false;
  char* temp = get_safe_new_data(str->data, str->len, new_data, new_data_len, &free_temp);
  if (!temp) {
    return ERR_ALLOC;
  }
  if (!ensure_capacity_insert(str, new_data_len)) {
    free_if_true(free_temp, temp);
    return ERR_ALLOC;
  }
  memmove(str->data + new_data_len, str->data, str->len);
  memcpy(str->data, temp, new_data_len);
  str->len += new_data_len;
  str->data[str->len] = '\0';
  free_if_true(free_temp, temp);
  return SUCCESS;
}

js_result js_clear(j_string* str) {
  if (str->len == 0) {
    return NOOP;
  }
  memset(str->data, 0, str->capacity + 1);
  str->len = 0;
  return SUCCESS;
}

js_result js_cpy(j_string* dest, const char* src) {
  return js_ncpy(dest, src, SIZE_MAX);
}
#include <ctype.h>

js_result js_insert(j_string* str, const char* new_data, size_t index) {
  if (!new_data || new_data[0] == '\0') {
    return NOOP;
  }
  if (index > str->len) {
    return ERR_RANGE;
  }

  size_t new_data_len = strlen(new_data);
  bool free_temp = false;
  char* temp = get_safe_new_data(str->data, str->len, new_data, new_data_len, &free_temp);
  if (!temp) {
    return ERR_ALLOC;
  }

  if (!ensure_capacity_insert(str, new_data_len)) {
    free_if_true(free_temp, temp);
    return ERR_ALLOC;
  }

  memmove(str->data + index + new_data_len, str->data + index, str->len - index);
  memcpy(str->data + index, temp, new_data_len);
  str->len += new_data_len;
  str->data[str->len] = '\0';
  free_if_true(free_temp, temp);
  return SUCCESS;
}

js_result js_pop_back(j_string* str) {
  if (str->len == 0) {
    return NOOP;
  }
  str->data[str->len - 1] = '\0';
  str->len--;
  return SUCCESS;
}

js_result js_pop_front(j_string* str) {
  if (str->len == 0) {
    return NOOP;
  }
  memmove(str->data, str->data + 1, str->len - 1);
  str->len--;
  str->data[str->len] = '\0';
  return SUCCESS;
}

js_result js_push_back(j_string* str, const char c) {
  if (c == '\0') {
    return ERR_INVALID_CHAR;
  }
  if (!ensure_capacity_insert(str, 1)) {
    return ERR_ALLOC;
  }
  str->data[str->len] = c;
  str->data[str->len + 1] = '\0';
  str->len++;
  return SUCCESS;
}

js_result js_push_front(j_string* str, const char c) {
  if (c == '\0') {
    return ERR_INVALID_CHAR;
  }
  if (!ensure_capacity_insert(str, 1)) {
    return ERR_ALLOC;
  }
  memmove(str->data + 1, str->data, str->len);
  str->data[0] = c;
  str->len++;
  str->data[str->len] = '\0';
  return SUCCESS;
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
