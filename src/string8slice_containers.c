#include "string8slice_containers.h"

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

