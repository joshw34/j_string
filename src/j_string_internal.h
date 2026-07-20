#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

typedef struct s_string {
  char* data;
  size_t len;
  size_t capacity;
} j_string;

const size_t MIN_CAPACITY = 32;

// utils.c
bool ensure_capacity_replace(j_string* str, size_t required);
bool ensure_capacity_insert(j_string* str, size_t to_add);
void free_if_true(bool flag, char* data);
char* get_safe_new_data(const char* data, size_t len, const char* new_data, size_t nd_len,
                        bool* free_temp);
void str_reverse(char* str);
