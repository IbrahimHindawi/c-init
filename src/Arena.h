#include <core.h>
#define N 1024
u8 store[N];

structdef(Arena) {
    u8 *mem;
    u8 *cursor;
    usize used;
};

typedef struct hkArray_Node hkArray_Node;
structdef(Node) {
    i32 length;
    // Node *nodes;
    hkArray_Node *nodes;
};

void arenaInit(Arena *arena, u8 *mem) {
    arena->mem = mem;
    arena->cursor = arena->mem;
    arena->used = 0;
}

void *arenaPush(Arena *arena, u64 allocsize) {
    if (arena->used + allocsize > N) {
        printf("Memory allocation failure! Maximum memory reached!\n");
        exit(-1);
    }
    arena->cursor += allocsize;
    return arena->cursor;
}

void *arenaPushZero(Arena *arena, u64 allocsize) {
    if (arena->used + allocsize > N) {
        printf("Memory allocation failure! Maximum memory reached!\n");
        exit(-1);
    }
    arena->cursor += allocsize;
    memcpy(arena->cursor, 0, allocsize);
    return arena->cursor;
}

// void *arenaRealloc(Arena *arena, u64 allocsize) {
//     arena->tail = arena->cursor;
//     return arenaPush(arena, allocsize);
// }

void arenaClear(Arena *arena) {
    arena->cursor = arena->mem;
}

void *arenaPop(Arena *arena, u64 allocsize) {
    arena->cursor -= allocsize;
    return arena->cursor;
}

void *arenaGetPos(Arena *arena) {
    return arena->cursor;
}

char *strAlloc(Arena *arena, char *input_str) {
    u64 input_str_len = strlen(input_str) + 1;
    char *output_str = arenaPush(arena, sizeof(i8) * input_str_len);
    memcpy(output_str, input_str, input_str_len);
    // output_str[0] = 'a';
    // for (i32 i = 0; i < input_str_len; ++i) {
    //     output_str[i] = input_str[i];
    // }
    return output_str;
}

void *strDealloc(Arena *arena, const char *input_str) {
    u64 input_str_len = strlen(input_str) + 1;
    return arenaPop(arena, input_str_len);
}

#define arenaPushStruct(arena, type) arenaPush(arena, sizeof(type))
#define arenaPushArray(arena, type, count) arenaPush(arena, sizeof(type) * count)
#define arenaPopArray(arena, type, count) arenaPop(arena, sizeof(type) * count)
#define arenaPushArrayZero(arena, type, count) arenaPushZero(arena, sizeof(type) * count)

