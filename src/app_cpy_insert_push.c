#include "j_string.h"
#include "j_string_internal.h"

// HELPERS

/* Ensure str->data capacity when replacing the string data entirely */
static bool ensure_capacity_replace(j_string* str, size_t required) {
  if (str->capacity >= required) {
    return true;
  }
  size_t new_capacity = (str->capacity == 0) ? 1 : str->capacity;
  while (new_capacity < required) {
    if (new_capacity > SIZE_MAX / 2) {
      return false;
    }
    new_capacity *= 2;
  }
  char* temp = realloc(str->data, new_capacity + 1);
  if (!temp) {
    return false;
  }
  str->data = temp;
  str->capacity = new_capacity;
  return true;
}

/* Ensure str->data capacity when adding to str->data */
static bool ensure_capacity_insert(j_string* str, size_t to_add) {
  size_t required = str->len + to_add;
  return ensure_capacity_replace(str, required);
}

static bool self_ref_check(const char* data, size_t len, const char* new_data) {
  return new_data >= data && new_data < data + len;
}

/* Returns a pointer safe to read new_data from even if str->data is later
   reallocated/freed. Allocates and copies only if new_data aliases str->data;
   sets *free_temp accordingly. */
static char* get_safe_new_data(const char* data, size_t len, const char* new_data,
                               size_t nd_len, bool* free_temp) {
  char* temp = NULL;
  if (self_ref_check(data, len, new_data)) {
    temp = malloc(nd_len + 1);
    if (!temp) {
      return NULL;
    }
    memcpy(temp, new_data, nd_len);
    temp[nd_len] = '\0';
    *free_temp = true;
  }
  else {
    temp = (char*)new_data;
  }
  return temp;
}

static void free_if_true(bool flag, char* data) {
  if (flag) {
    free(data);
  }
}

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

js_result js_cpy(j_string* dest, const char* src) {
  return js_ncpy(dest, src, SIZE_MAX);
}

js_result js_ncpy(j_string* dest, const char* src, size_t n) {
  if (!src || src[0] == '\0') {
    return NOOP;
  }
  size_t src_len = strlen(src);
  size_t cpy_len = (n < src_len) ? n : src_len;
  bool free_temp = false;
  char* temp = get_safe_new_data(dest->data, dest->len, src, cpy_len, &free_temp);
  if (!temp) {
    return ERR_ALLOC;
  }
  if (!ensure_capacity_replace(dest, cpy_len)) {
    free_if_true(free_temp, temp);
    return ERR_ALLOC;
  }
  memcpy(dest->data, temp, cpy_len);
  dest->data[cpy_len] = '\0';
  dest->len = cpy_len;
  free_if_true(free_temp, temp);
  return SUCCESS;
}

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
