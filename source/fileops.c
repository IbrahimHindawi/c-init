
#include <assert.h>
#include "fileops.h"

#define T f32
#include "hkArrayT.h"

typedef struct command {
    i32 x;
    i16 y;
} command;

void fops_read(const char *file_path) {
    FILE *fileptr;
    // fileptr = fopen(file_path, "r");

    fileptr = fopen(file_path, "r");
    fseek(fileptr, 0L, SEEK_END);
    u64 filesize = ftell(fileptr);
    fseek(fileptr, 0L, SEEK_SET);
    // printf("filesize = %lld\n", filesize);
    assert(filesize <= fops_buffer_size);
    if (fileptr != NULL) {
        size_t newlen = fread(fops_buffer, sizeof(char), fops_buffer_size, fileptr);
        if (ferror(fileptr) != 0) {
            fputs("error reading file!", stderr);
        } else {
            fops_buffer[newlen++] = '\0';
        }
    }
    fclose(fileptr);
    hkArrayf32 arrayf32 = hkArrayf32Create(8);
    for( int i = 0; i < arrayf32.length; ++i) {
        arrayf32.data[i] = i;
    }
    hkArrayf32Destroy(&arrayf32);
}
