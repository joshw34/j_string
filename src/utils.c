#include "j_string_internal.h"

/* Ensure str->data capacity when replacing the string data entirely */
bool ensure_capacity_replace(j_string* str, size_t required) {
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
bool ensure_capacity_insert(j_string* str, size_t to_add) {
  size_t required = str->len + to_add;
  return ensure_capacity_replace(str, required);
}

bool self_ref_check(const char* data, size_t len, const char* new_data) {
  return new_data >= data && new_data < data + len;
}

/* Returns a pointer safe to read new_data from even if str->data is later
   reallocated/freed. Allocates and copies only if new_data aliases str->data;
   sets *free_temp accordingly. */
char* get_safe_new_data(const char* data, size_t len, const char* new_data, size_t nd_len,
                        bool* free_temp) {
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

void free_if_true(bool flag, char* data) {
  if (flag) {
    free(data);
  }
}
