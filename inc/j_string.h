#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct s_string j_string;

typedef enum e_string_result {
  SUCCESS = 0,
  NOOP = 1,
  ERR_ALLOC = 2,
  ERR_INVALID_CHAR = 3,
  ERR_RANGE = 4,
} js_result;

typedef enum e_sort_type {
  ASCII = 0,
  LEN = 1,
  REV_ASCII = 2,
  REV_LEN = 3,
} sort_type;

// CREATE / FREE STRINGS
j_string* js_new(const char* data);
j_string* js_dup(const j_string* src);
j_string* js_join(const char* s1, const char* s2);
j_string* js_substr(const char* s, size_t start, size_t len);
j_string* js_trim(const char* s, const char* set);
j_string* js_itoa(int n);
j_string* js_uitoa(unsigned int n);
void js_free(j_string* str);

// MUTATE STRINGS
js_result js_app_back(j_string* str, const char* new_data);
js_result js_app_front(j_string* str, const char* new_data);
js_result js_clear(j_string* str);
js_result js_cpy(j_string* dest, const char* src);
js_result js_insert(j_string* str, const char* new_data, size_t index);
js_result js_ncpy(j_string* dest, const char* src, size_t n);
js_result js_pop_back(j_string* str);
js_result js_pop_front(j_string* str);
js_result js_push_back(j_string* str, char c);
js_result js_push_front(j_string* str, char c);
js_result js_remove(j_string* str, size_t start, size_t n);
js_result js_remove_back(j_string* str, size_t n);
js_result js_remove_front(j_string* str, size_t n);
js_result js_reverse(j_string* str);
js_result js_tolower(j_string* str);
js_result js_toupper(j_string* str);

// CREATE / FREE ARRAYS
j_string** js_array(const char** src);
j_string** js_empty_array(size_t size);
char** js_carray(const j_string** array);
j_string** js_split(const char* s, char c);
void js_free_array(j_string** array);

// MUTATE ARRAYS
js_result js_array_sort(j_string** array, sort_type type);

// ACCESSORS
size_t js_array_size(j_string** array);
char js_at(const j_string* str, size_t index);
const char* js_cstr(const j_string* str);
bool js_empty(const j_string* str);
size_t js_len(const j_string* str);
