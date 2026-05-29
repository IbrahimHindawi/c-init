#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "core.h"
#include "saha.h"

typedef uint8_t u8;
typedef uint64_t u64;

typedef struct string8 string8;
struct string8 {
    u8 *data;
    u64 length;
    u64 capacity;
};

typedef struct string8slice string8slice;
struct string8slice {
    u8 *data;
    u64 length;
};

#include "Vec_u8.h"
#include "Vec_string8.h"
#include "Vec_string8slice.h"

string8 string8_reserve(memops_arena *arena, u64 capacity);
string8 string8_from_cstr(memops_arena *arena, const char *cstr);
string8 string8_copy_from_slice(memops_arena *arena, u8 *data, u64 length);
char *string8_to_cstr_temp(memops_arena *arena, string8 string);

void string8_append_byte(memops_arena *arena, string8 *s, u8 byte);
void string8_append_bytes(memops_arena *arena, string8 *s, const u8 *src, u64 count);
void string8_append_cstr(memops_arena *arena, string8 *s, const char *cstr);

void string8_clear(string8 *s);

string8 string8_read_file(memops_arena *arena, const char *filename);

bool string8_equals(const string8 *a, const string8 *b);
bool string8_equals_cstr(const string8 *a, const char *cstr);

void string8_print(const string8 *s);

string8slice string8slice_from_parts(u8 *data, u64 length);
string8slice string8slice_sub(string8slice s, u64 start, u64 count);

bool string8slice_equals(string8slice a, string8slice b);
bool string8slice_equals_cstr(string8slice s, const char *cstr);

char *string8slice_to_cstr_temp(memops_arena *arena, string8slice s);

void string8slice_print(string8slice s);

Vec_string8 string8_split_char(memops_arena *arena, string8 src, char sep);
Vec_string8slice string8slice_split(memops_arena *arena, string8slice src, char sep);
Vec_string8slice string8slice_split_from_string8(memops_arena *arena, string8 s, char sep);
