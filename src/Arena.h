#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <core.h>
#define maxallocsize 0x10000000000

typedef struct Arena Arena;
struct Arena {
    u8 *base;
    u8 *cursor;
    u64 used;
    u64 pagesize;
    u64 npages;
};

typedef struct hkArray_Node hkArray_Node;
structdef(Node) {
    i32 length;
    // Node *nodes;
    hkArray_Node *nodes;
};

void arenaInit(Arena *arena) {
    SYSTEM_INFO systeminfo = {0};
    GetSystemInfo(&systeminfo);
    // printf("allocationgranularity = %lu\n", systeminfo.dwAllocationGranularity);
    // printf("page size = %lu\n", systeminfo.dwPageSize);
    arena->pagesize = systeminfo.dwPageSize; // 4096 or 0x1000
    arena->base = VirtualAlloc(NULL, maxallocsize, MEM_RESERVE, PAGE_NOACCESS); // reserve 1,099,511,627,776 bytes
    if (!arena->base) { exit(EXIT_FAILURE); }
    arena->cursor = arena->base;
}

void *arenaPush(Arena *arena, u64 allocsize) {
    if (arena->used + allocsize > arena->pagesize * arena->npages) {
        // align
        i32 npages = ceil((f32)(arena->used + allocsize) / arena->pagesize);
        arena->npages = npages;
        arena->base = VirtualAlloc(arena->base, arena->pagesize * arena->npages, MEM_COMMIT, PAGE_READWRITE);
        if (!arena->base) { exit(EXIT_FAILURE); }
    }
    if (arena->used > maxallocsize) {
        printf("Memory allocation failure! Maximum memory reached!\n");
        exit(EXIT_FAILURE);
    }
    arena->used += allocsize;
    void *oldpos = arena->cursor;
    arena->cursor += allocsize;
    return oldpos;
}

void *arenaPushZero(Arena *arena, u64 allocsize) {
    arenaPush(arena, allocsize);
    memcpy(arena->cursor, 0, allocsize);
    return arena->cursor;
}

void *arenaSetPos(Arena *arena, void *pos) {
    u64 diff = (u64)arena->cursor - (u64)pos;
    arena->used -= diff;
    arena->cursor = pos;
    return arena->cursor;
}

void arenaClear(Arena *arena) {
    arena->cursor = arena->base;
    arena->used = 0;
}

void *arenaPop(Arena *arena, u64 allocsize) {
    arena->cursor -= allocsize;
    arena->used -= allocsize;
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

void arenaPrint(Arena *arena) {
    printf("Memory Dump: %llu bytes allocated.\n", arena->used);
    printf("%p: ", arena->base);
    for (i32 i = 0; i < arena->used; ++i) {
        if(i % 8 == 0 && i != 0) {
            printf("\n");
            printf("%p: ", &arena->base[i]);
        }
        printf("%02x ", arena->base[i]);
    }
    printf("Memory Dump: End.\n");
}

#define arenaPushStruct(arena, type) arenaPush(arena, sizeof(type))
#define arenaPushArray(arena, type, count) arenaPush(arena, sizeof(type) * count)
#define arenaPopArray(arena, type, count) arenaPop(arena, sizeof(type) * count)
#define arenaPushArrayZero(arena, type, count) arenaPushZero(arena, sizeof(type) * count)
