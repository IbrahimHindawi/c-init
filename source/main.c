#include "core.h"
#include "fileops.h"

#define N 1024
u8 block[N];

int main(int argc, char *argv[]) {
    fops_read("C:\\devel\\c-init\\test.txt");
    printf("%s", fops_buffer);

    // initialize
    u8 *mem = block;
    u64 pos = (u64)block;
    
    // alloc 0
    const i32 numslen = 32;
    f32 *nums = (f32 *)pos;
    pos += sizeof(f32) * numslen;
    if ((pos - (u64)mem) > N) { return -1; }
    for (i32 i = 0; i < numslen; ++i) {
        nums[i] = (f32)i;
    }

    // alloc 1
    const i32 charlen = 0xFF;
    i8 *chars = (i8 *)pos;
    pos += sizeof(i8) * charlen;
    if ((pos - (u64)mem) > N) { return -1; }
    for (i32 i = 0; i < charlen; ++i) {
        chars[i] = (i8)i;
    }

    // dealloc all
    pos = (u64)mem;

    return 0;
}
