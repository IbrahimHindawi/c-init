#include "string8.h"
#include <string.h>
#include <stdio.h>

static void string8_terminate(string8 *s) {
    s->data[s->length] = 0;
}

string8 string8_reserve(memops_arena *arena, u64 capacity) {
    string8 s;
    s.data = memops_arena_push_array(arena, u8, capacity);
    s.length = 0;
    s.capacity = capacity;
    s.data[0] = 0;
    return s;
}

string8 string8_from_cstr(memops_arena *arena, const char *cstr) {
    u64 len = strlen(cstr);
    string8 s = string8_reserve(arena, len + 1);
    memcpy(s.data, cstr, len + 1);
    s.length = len;
    return s;
}

string8 string8_copy_from_slice(memops_arena *arena, u8 *data, u64 length) {
    string8 s = string8_reserve(arena, length + 1);
    memcpy(s.data, data, length);
    s.data[length] = 0;
    s.length = length;
    return s;
}

char *string8_to_cstr_temp(memops_arena *arena, string8 s) {
    char *out = memops_arena_push_array(arena, char, s.length + 1);
    memcpy(out, s.data, s.length);
    out[s.length] = 0;
    return out;
}

static void string8_grow(memops_arena *arena, string8 *s, u64 min_capacity) {
    Vec_u8 tmp;
    tmp.data = s->data;
    tmp.length = s->length + 1;
    tmp.border = s->capacity;

    while (tmp.border < min_capacity) {
        Vec_u8_resize(arena, &tmp);
    }

    s->data = tmp.data;
    s->capacity = tmp.border;
}

void string8_append_byte(memops_arena *arena, string8 *s, u8 byte) {
    if (s->length + 1 >= s->capacity)
        string8_grow(arena, s, s->length + 2);

    s->data[s->length] = byte;
    s->length++;
    string8_terminate(s);
}

void string8_append_bytes(memops_arena *arena, string8 *s, const u8 *src, u64 count) {
    if (s->length + count >= s->capacity)
        string8_grow(arena, s, s->length + count + 1);

    memcpy(s->data + s->length, src, count);
    s->length += count;
    string8_terminate(s);
}

void string8_append_cstr(memops_arena *arena, string8 *s, const char *cstr) {
    string8_append_bytes(arena, s, (const u8*)cstr, strlen(cstr));
}

void string8_clear(string8 *s) {
    s->length = 0;
    s->data[0] = 0;
}

string8 string8_read_file(memops_arena *arena, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return (string8){0};

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (size <= 0) {
        fclose(f);
        return (string8){0};
    }

    u8 *data = memops_arena_push_array(arena, u8, size + 1);
    fread(data, 1, size, f);
    fclose(f);

    data[size] = 0;

    string8 s;
    s.data = data;
    s.length = size;
    s.capacity = size + 1;
    return s;
}

bool string8_equals(const string8 *a, const string8 *b) {
    if (a->length != b->length) return false;
    return memcmp(a->data, b->data, a->length) == 0;
}

bool string8_equals_cstr(const string8 *a, const char *cstr) {
    u64 len = strlen(cstr);
    if (a->length != len) return false;
    return memcmp(a->data, cstr, len) == 0;
}

void string8_print(const string8 *s) {
    printf("%.*s\n", (int)s->length, s->data);
}

string8slice string8slice_from_parts(u8 *data, u64 length) {
    string8slice s;
    s.data = data;
    s.length = length;
    return s;
}

string8slice string8slice_sub(string8slice s, u64 start, u64 count) {
    if (start >= s.length) return (string8slice){0};
    if (start + count > s.length) count = s.length - start;

    string8slice out;
    out.data = s.data + start;
    out.length = count;
    return out;
}

bool string8slice_equals(string8slice a, string8slice b) {
    if (a.length != b.length) return false;
    return memcmp(a.data, b.data, a.length) == 0;
}

bool string8slice_equals_cstr(string8slice s, const char *cstr) {
    u64 len = strlen(cstr);
    if (s.length != len) return false;
    return memcmp(s.data, cstr, len) == 0;
}

char *string8slice_to_cstr_temp(memops_arena *arena, string8slice s) {
    char *out = memops_arena_push_array(arena, char, s.length + 1);
    memcpy(out, s.data, s.length);
    out[s.length] = 0;
    return out;
}

void string8slice_print(string8slice s) {
    printf("%.*s\n", (int)s.length, s.data);
}

Vec_string8 string8_split_char(memops_arena *arena, string8 src, char sep) {
    i32 count = 1;
    for (i32 i = 0; i < src.length; i++) {
        if (src.data[i] == (u8)sep) count++;
    }

    Vec_string8 out = Vec_string8_reserve(arena, count);

    u8 *start = src.data;
    u8 *end   = src.data + src.length;

    for (u8 *p = start; p < end; p++) {
        if (*p == (u8)sep) {
            i32 len = (i32)(p - start);
            Vec_string8_append(arena, &out, (string8){
                .data = start,
                .length = len,
            });
            start = p + 1;
        }
    }

    if (start <= end) {
        i32 len = (i32)(end - start);
        Vec_string8_append(arena, &out, (string8){
            .data = start,
            .length = len,
        });
    }

    return out;
}

Vec_string8slice string8slice_split(memops_arena *arena, string8slice src, char sep) {
    u64 count = 1;
    for (u64 i = 0; i < src.length; i++)
        if (src.data[i] == sep) count++;

    Vec_string8slice out = Vec_string8slice_reserve(arena, count);

    u8 *start = src.data;
    u8 *end = src.data + src.length;

    for (u8 *p = start; p < end; p++) {
        if (*p == sep) {
            Vec_string8slice_append(arena, &out,
                string8slice_from_parts(start, (u64)(p - start)));
            start = p + 1;
        }
    }

    Vec_string8slice_append(arena, &out,
        string8slice_from_parts(start, (u64)(end - start)));

    return out;
}

Vec_string8slice string8slice_split_from_string8(memops_arena *arena, string8 s, char sep) {
    u64 count = 1;
    for (u64 i = 0; i < s.length; i++) {
        if (s.data[i] == (u8)sep) count++;
    }

    Vec_string8slice out = Vec_string8slice_reserve(arena, count);

    u8 *start = s.data;
    u8 *end = s.data + s.length;

    for (u8 *p = start; p < end; p++) {
        if (*p == (u8)sep) {
            Vec_string8slice_append(arena, &out,
                string8slice_from_parts(start, (u64)(p - start)));
            start = p + 1;
        }
    }

    Vec_string8slice_append(arena, &out,
        string8slice_from_parts(start, (u64)(end - start)));

    return out;
}
