#define N 1024
u8 store[N];

structdef(Arena) {
    u8 *mem;
    u8 *head;
    u8 *tail;
};

void arenaInit(Arena *arena, u8 *mem) {
    arena->mem = mem;
    arena->head = arena->mem;
    arena->tail = arena->mem;
}

void *arenaPush(Arena *arena, u64 size) {
    if ((arena->tail + size) - arena->mem > N) {
        printf("Memory allocation failure! Maximum memory reached!\n");
        exit(-1);
    }
    arena->head = arena->tail;
    arena->tail += size;
    return arena->head;
}

void *arenaPushZero(Arena *arena, u64 size) {
    arena->head = arena->tail;
    arena->tail += size;
    memcpy(arena->head, 0, size);
    return arena->head;
}

void *arenaRealloc(Arena *arena, u64 size) {
    arena->tail = arena->head;
    return arenaPush(arena, size);
}

void arenaClear(Arena *arena) {
    arena->head = arena->mem;
    arena->tail = arena->mem;
}

void *arenaPop(Arena *arena, u64 size) {
    arena->tail -= size;
    arena->head = arena->tail;
    return arena->head;
}

void *arenaGetPos(Arena *arena) {
    return arena->head;
}

i8 *strAlloc(Arena *arena, i8 *input_str) {
    u64 input_str_len = strlen(input_str) + 1;
    i8 *output_str = arenaPush(arena, sizeof(i8) * input_str_len);
    memcpy(output_str, input_str, input_str_len);
    // output_str[0] = 'a';
    // for (i32 i = 0; i < input_str_len; ++i) {
    //     output_str[i] = input_str[i];
    // }
    return output_str;
}

void *strDealloc(Arena *arena, const i8 *input_str) {
    u64 input_str_len = strlen(input_str) + 1;
    return arenaPop(arena, input_str_len);
}

#define arenaPushStruct(arena, type) arenaPush(arena, sizeof(type))
#define arenaPushArray(arena, type, count) arenaPush(arena, sizeof(type) * count)
#define arenaPopArray(arena, type, count) arenaPop(arena, sizeof(type) * count)
#define arenaPushArrayZero(arena, type, count) arenaPushZero(arena, sizeof(type) * count)

