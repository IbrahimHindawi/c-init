#define SAHA_IMPLEMENTATION
#include <saha.h>

#define CORE_IMPL
#include <core.h>

template(Vec(u8));

#include <Vec.h>

i32 main(i32 argc, char *argv[]) {
    memops_arena arena = {};
    memops_arena_initialize(&arena);
    memops_arena_temp scope = memops_arena_temp_begin(&arena);
    {
        Vec_u8 numbers = Vec_u8_reserve(&arena, 128);
        for (i32 i = 0; i < 128; i += 1) {
            numbers.data[i] = i;
        }
        numbers.data[0] = 'b';
        numbers.data[1] = 'u';
        numbers.data[2] = 'n';
        numbers.data[3] = 'y';
        numbers.data[4] = 'a';
        numbers.data[5] = 'n';
        printf("%s\n", numbers.data);
    }
    memops_arena_temp_end(scope);
    return 0;
}

#include <Vec.c>
