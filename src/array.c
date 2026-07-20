#include "j_string.h"
#include "j_string_internal.h"

static size_t str_array_size(const char** array) {
  size_t i = 0;
  if (!array) {
    return 0;
  }
  while (array[i]) {
    i++;
  }
  return i;
}

static void free_str_array(char** array) {
  if (!array) {
    return;
  }
  for (size_t i = 0; array[i]; ++i) {
    free(array[i]);
  }
  free((void*)array);
}

static bool array_should_swap(const j_string* s1, const j_string* s2, sort_type type) {
  size_t min_len = (s1->len < s2->len) ? s1->len : s2->len;
  int cmp = strncmp(s1->data, s2->data, min_len);
  switch (type) {
    case ASCII:
      return cmp != 0 ? cmp > 0 : s1->len > s2->len;
    case LEN:
      return s1->len != s2->len ? s1->len > s2->len : cmp > 0;
    case REV_ASCII:
      return cmp != 0 ? cmp < 0 : s1->len < s2->len;
    case REV_LEN:
      return s1->len != s2->len ? s1->len < s2->len : cmp < 0;
  }
  return false;
}

js_result js_array_sort(j_string** array, sort_type type) {
  if (type != ASCII && type != LEN && type != REV_ASCII && type != REV_LEN) {
    return NOOP;
  }
  size_t size = js_array_size(array);
  if (size < 2) {
    return NOOP;
  }
  for (size_t i = 0; i < size - 1; ++i) {
    for (size_t j = 0; j < size - 1 - i; j++) {
      if (array_should_swap(array[j], array[j + 1], type)) {
        j_string* temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
  return SUCCESS;
}

void js_free_array(j_string** array) {
  if (!array) {
    return;
  }
  for (size_t i = 0; array[i]; ++i) {
    js_free(array[i]);
  }
  free((void*)array);
}

char** js_carray(const j_string** array) {
  if (!array) {
    return NULL;
  }
  size_t size = js_array_size((j_string**)array);
  char** result = (char**)malloc((size + 1) * sizeof(char*));
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; array[i]; ++i) {
    result[i] = malloc(array[i]->len + 1);
    if (!result[i]) {
      free_str_array(result);
      return NULL;
    }
    memcpy(result[i], array[i]->data, array[i]->len);
    result[i][array[i]->len] = '\0';
  }
  return result;
}

j_string** js_empty_array(size_t size) {
  j_string** result = (j_string**)malloc((size + 1) * sizeof(j_string*));
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; i < size; ++i) {
    result[i] = js_new("");
    if (!result[i]) {
      js_free_array(result);
      return NULL;
    }
  }
  return result;
}

j_string** js_array(const char** src) {
  if (!src) {
    return NULL;
  }
  size_t src_size = str_array_size(src);
  j_string** result = (j_string**)malloc((src_size + 1) * sizeof(j_string*));
  if (!result) {
    return NULL;
  }
  for (size_t i = 0; src[i]; ++i) {
    result[i] = js_new(src[i]);
    if (!result[i]) {
      js_free_array(result);
      return NULL;
    }
  }
  return result;
}
